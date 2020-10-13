#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);

	ECS::Create(0);
	ECS::Add<Camera>(0);
	ECS::Get<Camera>(0).SetPosition(glm::vec3(0, 1, -1));
	ECS::Get<Camera>(0).LookAt(glm::vec3(0.0f));
	
}

void Scene::Update()
{
	
}