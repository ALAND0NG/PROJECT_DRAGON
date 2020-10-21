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
	
}

void Scene::Update()
{
	
}