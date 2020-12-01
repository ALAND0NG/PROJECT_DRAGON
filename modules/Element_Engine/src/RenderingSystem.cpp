#include <RenderingSystem.h>
#include <IMGUIManager.h>
#include <string>

Shader::sptr RenderingSystem::shader = nullptr;
Shader::sptr RenderingSystem::AnimationShader = nullptr;
Shader::sptr RenderingSystem::BlendShader = nullptr;
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

	//init attenuation
	shader->SetUniform("u_LightAttenuationConstant", 1.f);
	shader->SetUniform("u_LightAttenuationLinear", 0.08f);
	shader->SetUniform("u_LightAttenuationQuadratic", 0.032f);

	//init attenuation
	AnimationShader->SetUniform("u_LightAttenuationConstant", 1.f);
	AnimationShader->SetUniform("u_LightAttenuationLinear", 0.08f);
	AnimationShader->SetUniform("u_LightAttenuationQuadratic", 0.032f);

	IMGUIManager::imGuiCallbacks.push_back([&]()
		{		// We'll add some ImGui controls to control our shader

			//ImGui::DragFloat("Enemy Light Ambient R", &ECS::Get<LightSource>(2).m_Diffuse.x, 1.f, 0.f, 3.f, "%.1f", 1.f);
		});

	//initialize primary fragment shader DirLight & spotlight
	shader->SetUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader->SetUniform("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
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
	
	auto reg = ECS::GetReg();
	int LightCount = 0;

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


		
		LightCount++;
	}
	

	


	shader->SetUniform("u_LightCount", LightCount);
	AnimationShader->SetUniform("u_LightCount", LightCount);
}
