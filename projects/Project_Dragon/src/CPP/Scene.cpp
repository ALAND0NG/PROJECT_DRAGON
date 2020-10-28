#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(0.f, 0.f, 0.f));
	ECS::Add<Camera>(0);
	//ECS::Get<Camera>(0).SetUp(glm::vec3(0, 1, 0));
	
	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Transform>(1);
	

	ECS::Get<Transform>(1).SetPosition(glm::vec3(1.f, -9.f, 1.f));
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadDiffuse2FromFile("images/thanos.jpg"); //used for texture blending
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).Tex1Str = 0.5f;
	ECS::Get<Material>(1).Tex2Str = 0.9f;
	ECS::Get<Material>(1).SetAll(0.1f);

	ECS::Create(2);
	ECS::Add<LightSource>(2);
	ECS::Add<Transform>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(5.f, -9.f, 0.f));
	

}

void Scene::Update()
{
	
}