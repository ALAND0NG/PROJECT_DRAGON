#include <RenderingSystem.h>
#include <IMGUIManager.h>

Shader::sptr RenderingSystem::shader = nullptr;
Shader::sptr RenderingSystem::AnimationShader = nullptr;
void RenderingSystem::Init()
{
	//Inits all shader constants
	
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	AnimationShader = Shader::Create();
	AnimationShader->LoadShaderPartFromFile("shader/morph_vert.glsl", GL_VERTEX_SHADER);
	AnimationShader->LoadShaderPartFromFile("shader/morph_frag.glsl", GL_FRAGMENT_SHADER);
	AnimationShader->Link();
	


	//Set these values to your liking
	float     lightAmbientPow = 0.1f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(0.1f, 0.1f, 0.1f);
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
	
	int frameIx = 0;
	float fpsBuffer[128];
	float minFps, maxFps, avgFps;
	int selectedVao = 0; // select cube by default

	IMGUIManager::imGuiCallbacks.push_back([&]()
		{		// We'll add some ImGui controls to control our shader
		
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

		});
}

void RenderingSystem::Update()
{
	ECSUpdate();
}

void RenderingSystem::ECSUpdate()
{
	auto reg = ECS::GetReg();
	int LightCount = 0;

	for (int i = 0; i < reg->size(); i++)
	{
		shader->Bind();
		
		if (ECS::Has<Parent>(i))
		{
			ECS::Get<Transform>(i).SetPosition(ECS::Get<Transform>(ECS::Get<Parent>(i).GetParent()).GetPosition() + ECS::Get<Transform>(i).GetPosition());
		}

		
		if (ECS::Has<LightSource>(i) && ECS::Has<Transform>(i))
		{

			shader->SetUniform("LightPositions[" + std::to_string(LightCount) + "]", ECS::Get<Transform>(i).GetPosition());
			shader->SetUniform("u_LightCol", ECS::Get<LightSource>(i).m_Colour);
			LightCount++;
		}

		if (ECS::Has<Transform>(i) && ECS::Has<Camera>(i))
		{
			//Just updates camera stuff with tranform stuff to keep it consistent
			ECS::Get<Camera>(i).SetPosition(ECS::Get<Transform>(i).GetPosition());
			
		}

		if (ECS::Has<Transform>(i) == 1 && ECS::Has<Mesh>(i) == 1 && ECS::Has<Material>(i) == 1)
		{
			ECS::Get<Transform>(i).ComputeGlobalMat();


			//I know that I could properly get the camera, but as a convention we will simply always declare it as entity 0 to avoid coding an entity
			//identitifier
			shader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * ECS::Get<Transform>(i).GetTransform());
			shader->SetUniformMatrix("u_Model", ECS::Get<Transform>(i).GetTransform());
			//shader->SetUniformMatrix("u_ModelRotation", glm::toMat3(ECS::Get<Transform>(i).GetRotation()));
			shader->SetUniform("u_CamPos", ECS::Get<Camera>(0).GetPosition());

			// Tell OpenGL that slot 0 will hold the diffuse, and slot 1 will hold the specular
			shader->SetUniform("s_Diffuse", 0);
			shader->SetUniform("s_Specular", 1);
			

			ECS::Get<Material>(i).GetAlbedo()->Bind(0);

			ECS::Get<Material>(i).GetSpecular()->Bind(1);

		

			shader->SetUniform("u_Shininess", ECS::Get<Material>(i).GetShininess());

			ECS::Get<Mesh>(i).GetVAO()->Render();
		}

		if (ECS::Has<Transform>(i) == 1 && ECS::Has<MorphAnimator>(i) == 1 && ECS::Has<Material>(i) == 1)
		{
			
			AnimationShader->Bind();


			//I know that I could properly get the camera, but as a convention we will simply always declare it as entity 0 to avoid coding an entity
			//identitifier
			AnimationShader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * ECS::Get<Transform>(i).GetTransform());
			AnimationShader->SetUniformMatrix("u_Model", ECS::Get<Transform>(i).GetTransform());
			//shader->SetUniformMatrix("u_ModelRotation", glm::toMat3(ECS::Get<Transform>(i).GetRotation()));
			AnimationShader->SetUniform("u_CamPos", ECS::Get<Camera>(0).GetPosition());

			// Tell OpenGL that slot 0 will hold the diffuse, and slot 1 will hold the specular
			AnimationShader->SetUniform("s_Diffuse", 0);
			AnimationShader->SetUniform("s_Specular", 1);


			ECS::Get<Material>(i).GetAlbedo()->Bind(0);

			ECS::Get<Material>(i).GetSpecular()->Bind(1);



			AnimationShader->SetUniform("u_Shininess", ECS::Get<Material>(i).GetShininess());
			AnimationShader->SetUniform("t", ECS::Get<MorphAnimator>(i).GetAnimData().t);

			ECS::Get<MorphAnimator>(i).Update();
			ECS::Get<MorphAnimator>(i).GetVAO()->Render();
			
		}

	}

	shader->SetUniform("u_LightCount", LightCount);
	AnimationShader->SetUniform("u_LightCount", LightCount);
}
