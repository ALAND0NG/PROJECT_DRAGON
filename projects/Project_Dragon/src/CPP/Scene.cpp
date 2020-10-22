#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Camera>(0);
	
	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Transform>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(1.f, 1.f, 1.f));
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj");
	

	ECS::Create(2);
	ECS::Add<Mesh>(2);
	ECS::Add<Transform>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(-5.f, 0.f, 0.f));
	ECS::Get<Mesh>(2).LoadOBJ("Models/monkey.obj");
	

	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Transform>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(-5.f, -5.f, -5.f));
	ECS::Get<Mesh>(3).LoadOBJ("Models/monkey.obj");

	
	ECS::Create(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Transform>(4);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(2.f, 1.f, 5.f));
	ECS::Get<Mesh>(4).LoadOBJ("Models/earth.obj");
		
	ECS::Create(5);
	ECS::Add<Mesh>(5);
	ECS::Add<Transform>(5);
	ECS::Get<Mesh>(5).SetVAO(ECS::Get<Mesh>(1).GetVAO());

	for (int i = 6; i < 20; i++)
	{
		ECS::Create(i);
		ECS::Add<Mesh>(i);
		ECS::Add<Transform>(i);
		ECS::Get<Transform>(i).SetPosition(glm::vec3(i *2.f, i *2.f, 0.f));
		ECS::Get<Mesh>(i).SetVAO(ECS::Get<Mesh>(4).GetVAO());
	}

}

void Scene::Update()
{
	
}