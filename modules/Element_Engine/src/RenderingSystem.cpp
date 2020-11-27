#include <RenderingSystem.h>
#include <IMGUIManager.h>

Shader::sptr RenderingSystem::shader = nullptr;
Shader::sptr RenderingSystem::AnimationShader = nullptr;
Shader::sptr RenderingSystem::BlendShader = nullptr;
void RenderingSystem::Init()
{
	//Inits all shader constants
	
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	AnimationShader = Shader::Create();
	AnimationShader->LoadShaderPartFromFile("shader/morph_vert.glsl", GL_VERTEX_SHADER);
	AnimationShader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	AnimationShader->Link();
	
	BlendShader = Shader::Create();
	BlendShader->LoadShaderPartFromFile("shader/blending_vert.glsl", GL_VERTEX_SHADER);
	BlendShader->LoadShaderPartFromFile("shader/morph_frag.glsl", GL_FRAGMENT_SHADER);
	BlendShader->Link();



	//Set these values to your liking
	float     lightAmbientPow = 0.5f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.f, 1.f, 1.f);
	float     ambientPow = 0.1f;
	float     shininess = 1.0f;
	float     lightLinearFalloff = 0.09f;
	float     lightQuadraticFalloff = 0.032f;



	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);
	shader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	shader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);

	AnimationShader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	AnimationShader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	AnimationShader->SetUniform("u_AmbientCol", ambientCol);
	AnimationShader->SetUniform("u_AmbientStrength", ambientPow);
	AnimationShader->SetUniform("u_Shininess", shininess);
	AnimationShader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	AnimationShader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);

	BlendShader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	BlendShader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	BlendShader->SetUniform("u_AmbientCol", ambientCol);
	BlendShader->SetUniform("u_AmbientStrength", ambientPow);
	BlendShader->SetUniform("u_Shininess", shininess);
	BlendShader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	BlendShader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);
	
	int frameIx = 0;
	float fpsBuffer[128];
	float minFps, maxFps, avgFps;
	int selectedVao = 0; // select cube by default

	IMGUIManager::imGuiCallbacks.push_back([&]()
		{		// We'll add some ImGui controls to control our shader
			/*
			if (ImGui::Button("Play Animation 1"))
			{
				ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);
			}
			if (ImGui::Button("Play Animation 2"))
			{
				ECS::Get<MorphAnimator>(2).SetActiveAnimation(1);
			}
			if (ImGui::Button("Play Animation 3"))
			{
				ECS::Get<MorphAnimator>(2).SetActiveAnimation(2);
			}

			if (ImGui::Button("Make thing go into a box : )"))
			{
				ECS::Get<MorphAnimator>(2).SetActiveAnimation(3);
			}
		
			//ImGui::DragFloat("Animation Blending", &ECS::Get<Blender>(3).shaderBlend, 1.f, 0.f, 1.f, "%.1f", 1.f);
		
			*/
			if (ImGui::Button("Move ent 2"))
			{
				glm::vec3 pos = ECS::Get<Transform>(2).GetPosition();
				pos.x += 1.f;
				ECS::Get<Transform>(2).SetPosition(pos);
			}

			
		});
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
	
	auto reg = ECS::GetReg();
	int LightCount = 0;

	//view for Mesh
	auto view = reg->view<Mesh, Transform, Material>();
	for (auto entity : view)
	{
		shader->Bind();

		auto& mesh = view.get<Mesh>(entity);
		auto& trns = view.get<Transform>(entity);
		auto& mat = view.get<Material>(entity);

		trns.ComputeGlobalMat();

		shader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * trns.GetTransform());
		shader->SetUniformMatrix("u_Model", trns.GetTransform());

		mat.GetAlbedo()->Bind(0);

		mat.GetSpecular()->Bind(1);

		shader->SetUniform("u_Shininess", mat.GetShininess());

		mesh.GetVAO()->Render();
	}
	
	//view for lightsource
	auto lview = reg->view<LightSource, Transform>();
	for (auto entity : lview)
	{

		auto& trns = lview.get<Transform>(entity);
		auto& lsrc = lview.get<LightSource>(entity);

		shader->SetUniform("LightPositions[" + std::to_string(LightCount) + "]", trns.GetPosition());
		shader->SetUniform("u_LightCol", lsrc.m_Colour);
		AnimationShader->SetUniform("LightPositions[" + std::to_string(LightCount) + "]", trns.GetPosition());
		AnimationShader->SetUniform("u_LightCol", lsrc.m_Colour);
		LightCount++;
	}
	
	//view for morph animator
	auto mview = reg->view<MorphAnimator, Transform, Material>();
	for (auto entity : mview)
	{
		AnimationShader->Bind();

		auto& manim = mview.get<MorphAnimator>(entity);
		auto& trns = mview.get<Transform>(entity);
		auto& mat = mview.get<Material>(entity);

		trns.ComputeGlobalMat();

		AnimationShader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * trns.GetTransform());
		AnimationShader->SetUniformMatrix("u_Model", trns.GetTransform());

	
		// Tell OpenGL that slot 0 will hold the diffuse, and slot 1 will hold the specular
		AnimationShader->SetUniform("s_Diffuse", 0);
		AnimationShader->SetUniform("s_Specular", 1);

		mat.GetAlbedo()->Bind(0);
		mat.GetSpecular()->Bind(1);


		AnimationShader->SetUniform("u_Shininess", mat.GetShininess());
		AnimationShader->SetUniform("t", manim.GetAnimData().t);
	}
	


	shader->SetUniform("u_LightCount", LightCount);
	AnimationShader->SetUniform("u_LightCount", LightCount);
}
