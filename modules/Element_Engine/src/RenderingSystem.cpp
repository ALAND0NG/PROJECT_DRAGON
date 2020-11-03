#include <RenderingSystem.h>

Shader::sptr RenderingSystem::shader = nullptr;

void RenderingSystem::Init()
{
	//Inits all shader constants
	
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();


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
			shader->SetUniform("s_Diffuse2", 2);//remove to only have 1 texture

			ECS::Get<Material>(i).GetAlbedo()->Bind(0);

			ECS::Get<Material>(i).GetSpecular()->Bind(1);

			ECS::Get<Material>(i).GetAlbedo2()->Bind(2);//Remove to only have 1 texture

			shader->SetUniform("u_Shininess", ECS::Get<Material>(i).GetShininess());
			shader->SetUniform("Tex1Str", ECS::Get<Material>(i).Tex1Str);
			shader->SetUniform("Tex2Str", ECS::Get<Material>(i).Tex2Str);

			ECS::Get<Mesh>(i).GetVAO()->Render();
		}
		if (ECS::Has<Transform>(i) && ECS::Has<LightSource>(i))
		{
			//shader->SetUniform("u_LightPos", ECS::Get<Transform>(i).GetPosition());
		}
	}

	shader->SetUniform("u_LightCount", LightCount);
}
