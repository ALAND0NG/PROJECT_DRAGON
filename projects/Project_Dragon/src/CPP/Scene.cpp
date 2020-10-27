#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(0.f, -50.f, 0.f));
	ECS::Add<Camera>(0);
	
	/*
	ECS::Create(entity number);
	ECS::Add<Mesh>(entity number);
	ECS::Add<Transform>(entity number);
	ECS::Get<Transform>(entity number).SetPosition(glm::vec3(1.f, -2.f, 1.f));
	ECS::Get<Mesh>(entity number).LoadOBJ("path", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); this vec4 is the color
	ECS::Add<Material>(entity number);
	ECS::Get<Material>(entity number).LoadDiffuseFromFile("file path");
	ECS::Get<Material>(entity number).LoadSpecularFromFile("file path");
	ECS::Get<Material>(entity number).SetAll(0.1f); //this is the shiniess also sets other stuff
	*/


	/*
	EXAMPLE CREATE LIGHT FOR NOW ONLY 1 OF THEM ILL PUSH TO MASTER WHEN MULTIPLE LIGHTS WORKS
	ECS::Create(entity number);
	ECS::Add<Transform>(entity number);
	ECS::Add<LightSource>(entity number);
	ECS::Get<LightSource>(entity number).m_Colour = glm::vec3(0.5, 1.f, 1.f);
	ECS::Get<Transform>(entity number).SetPosition(glm::vec3(5.f, -9.f, -7.f));
	*/
	




}

void Scene::Update()
{
	
}