#include <RenderingSystem.h>
#include <IMGUIManager.h>
#include <string>
#include <Interpolation.h>
#include "BackEnd.cpp"

Shader::sptr RenderingSystem::shader = nullptr;
Shader::sptr RenderingSystem::AnimationShader = nullptr;
Shader::sptr RenderingSystem::BlendShader = nullptr;
Shader::sptr RenderingSystem::UIShader = nullptr;

//uiscale
float uiScalex = 1.f;
float uiScaley = 0.7f;
void RenderingSystem::Init()
{
	//Inits all shaders
	
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	AnimationShader = Shader::Create();
	AnimationShader->LoadShaderPartFromFile("shader/morph_vert.glsl", GL_VERTEX_SHADER);
	AnimationShader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	AnimationShader->Link();

	UIShader = Shader::Create();
	UIShader->LoadShaderPartFromFile("shader/ui_vert.glsl", GL_VERTEX_SHADER);
	UIShader->LoadShaderPartFromFile("shader/ui_frag.glsl", GL_FRAGMENT_SHADER);
	UIShader->Link();
	//init attenuation
	shader->SetUniform("u_LightAttenuationConstant", 1.f);
	shader->SetUniform("u_LightAttenuationLinear", 0.08f);
	shader->SetUniform("u_LightAttenuationQuadratic", 0.032f);

	//init attenuation
	AnimationShader->SetUniform("u_LightAttenuationConstant", 1.f);
	AnimationShader->SetUniform("u_LightAttenuationLinear", 0.08f);
	AnimationShader->SetUniform("u_LightAttenuationQuadratic", 0.032f);


	//initialize primary fragment shader DirLight & spotlight
	shader->SetUniform("dirLight.direction", glm::vec3(-0.0f, -1.0f, -0.0f));
	shader->SetUniform("dirLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->SetUniform("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader->SetUniform("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	//initialize primary fragment shader DirLight & spotlight
	AnimationShader->SetUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	AnimationShader->SetUniform("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	AnimationShader->SetUniform("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	AnimationShader->SetUniform("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

}


void RenderingSystem::Update()
{
	ECSUpdate();
}

float LightVal1 = 0.4;
float LightVal2 = 1;

float t = 0;
float t2 = 0.99f;
bool isForward = true;

void RenderingSystem::ECSUpdate()
{


	//Just updates camera stuff with tranform stuff to keep it consistent
	ECS::Get<Camera>(0).SetPosition(ECS::Get<Transform>(0).GetPosition());

	shader->SetUniform("u_CamPos", ECS::Get<Camera>(0).GetPosition());
	AnimationShader->SetUniform("u_CamPos", ECS::Get<Camera>(0).GetPosition());


	// Tell OpenGL that slot 0 will hold the diffuse, and slot 1 will hold the specular
	shader->SetUniform("s_Diffuse", 0);
	shader->SetUniform("s_Specular", 1);

	AnimationShader->SetUniform("s_Diffuse", 0);
	AnimationShader->SetUniform("s_Specular", 1);

	UIShader->SetUniform("s_Specular", 0);
	UIShader->SetUniform("s_Diffuse", 1);
	UIShader->SetUniform("u_IsMenu", 1);
	
	auto reg = ECS::GetReg();
	int LightCount = 0;

	
	auto Parentingview = reg->view<Parent, Transform>();
	for (auto entity : Parentingview)
	{
		Parent& parent = Parentingview.get<Parent>(entity);
		Transform& trans = Parentingview.get<Transform>(entity);

		trans.SetModelMat(trans.GetTransform() * ECS::Get<Transform>(parent.GetParent()).GetTransform());
		trans.ComputeGlobalMat();
	}
	
	//updates the enemies
	auto enemyView = reg->view<Enemy>();
	for (auto entity : enemyView)
	{
		Enemy& enemy = enemyView.get<Enemy>(entity);
		enemy.Update();
	}




	//view for Mesh
	auto view = reg->view<Mesh, Transform, Material>();
	for (auto entity : view)
	{
		shader->Bind();

		Mesh& mesh = view.get<Mesh>(entity);
		Transform& trns = view.get<Transform>(entity);
		Material& mat = view.get<Material>(entity);

		trns.ComputeGlobalMat();

		shader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * trns.GetTransform());
		shader->SetUniformMatrix("u_Model", trns.GetTransform());

		mat.GetAlbedo()->Bind(0);

		mat.GetSpecular()->Bind(1);

		shader->SetUniform("u_Shininess", mat.GetShininess());

		mesh.GetVAO()->Render();
	}
	
	//view for morph animator
	auto mview = reg->view<MorphAnimator, Transform, Material>();
	for (auto entity : mview)
	{
		AnimationShader->Bind();

		MorphAnimator& manim = mview.get<MorphAnimator>(entity);
		Transform& trns = mview.get<Transform>(entity);
		Material& mat = mview.get<Material>(entity);

		trns.ComputeGlobalMat();

		AnimationShader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * trns.GetTransform());
		AnimationShader->SetUniformMatrix("u_Model", trns.GetTransform());


		mat.GetAlbedo()->Bind(0);
		mat.GetSpecular()->Bind(1);


		AnimationShader->SetUniform("u_Shininess", mat.GetShininess());
		AnimationShader->SetUniform("t", manim.GetAnimData().t);
		manim.Update();
		manim.GetVAO()->Render();
	}

	//view for UI
	auto UIview = reg->view<UI, LightSource>(); 
	for (auto entity : UIview)
	{
		UIShader->Bind();

		UIShader->SetUniform("u_IsMenu", 0);

		UI& ui = UIview.get<UI>(entity);

	
		t2 = 0.2 * ECS::Get<Player>(0).GetPlayerData().m_HP;
	
		uiScalex = Interpolation::LERP(0,1, t2);

		glm::vec2 scale = glm::vec2(uiScalex, uiScaley);

		UIShader->SetUniform("u_Scale", scale);
		UIShader->SetUniform("u_Offset", glm::vec2(0, 0.9));
		
		ui.material.GetAlbedo()->Bind(0);
		ui.material.GetSpecular()->Bind(1);


		ui.mesh.GetVAO()->Render();

	}

	auto Menuview = reg->view<UI, Menu>();
	for (auto entity : Menuview)
	{
		UIShader->Bind();

		UI& ui = Menuview.get<UI>(entity);


		UIShader->SetUniform("u_IsMenu", 1);

		UIShader->SetUniform("u_Scale", glm::vec2(1,1.5));
		UIShader->SetUniform("u_Offset", glm::vec2(0, 0.7));

		ui.material.GetAlbedo()->Bind(0);
		ui.material.GetSpecular()->Bind(1);


		ui.mesh.GetVAO()->Render();

	}


	//view for lightsource
	auto lview = reg->view<LightSource, Transform>(); 
	for (auto entity : lview)
	{

		Transform& trns = lview.get<Transform>(entity);
		LightSource& lsrc = lview.get<LightSource>(entity);

		if (LightCount <= 50)
		{
			//create the string to send to the shader
			std::string uniformName;
			uniformName = "pointLights[";
			uniformName += std::to_string(LightCount);
			uniformName += "].";
			//this will be the begining, now we just need to add the part of the struct we want to set
			shader->SetUniform(uniformName + "position", trns.GetPosition());
			shader->SetUniform(uniformName + "ambient", lsrc.m_Ambient);
			shader->SetUniform(uniformName + "diffuse", lsrc.m_Diffuse);
			shader->SetUniform(uniformName + "specular", lsrc.m_Specular);
			shader->SetUniform("u_LightCount", LightCount);
		}

		if (LightCount <= 50)
		{
			//create the string to send to the shader
			std::string uniformName;
			uniformName = "pointLights[";
			uniformName += std::to_string(LightCount);
			uniformName += "].";
			//this will be the begining, now we just need to add the part of the struct we want to set
			AnimationShader->SetUniform(uniformName + "position", trns.GetPosition());
			AnimationShader->SetUniform(uniformName + "ambient", lsrc.m_Ambient);
			AnimationShader->SetUniform(uniformName + "diffuse", lsrc.m_Diffuse);
			AnimationShader->SetUniform(uniformName + "specular", lsrc.m_Specular);
			AnimationShader->SetUniform("u_LightCount", LightCount);
		}

		//Does a LERP for enemy light

		auto EnLiView = reg->view<LightSource, Enemy>();

		for (auto entity : EnLiView)
		{

		
			LightSource& liSrc = EnLiView.get<LightSource>(entity);

			if (t >= 1 && t > 0)
				isForward = false;
			if (t <= 0)
				isForward = true;

			if (isForward)
				t += Timer::dt * 0.001f;
			else
				t -= Timer::dt * 0.001f;

			liSrc.m_Ambient.x = Interpolation::LERP(LightVal1, LightVal2, t);

		}
		
		LightCount++;
	}
	

	


	shader->SetUniform("u_LightCount", LightCount);
	AnimationShader->SetUniform("u_LightCount", LightCount);
}
