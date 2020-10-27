#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(0.f, -50.f, 0.f));
	ECS::Add<Camera>(0);
	//ECS::Get<Camera>(0).SetUp(glm::vec3(0, 1, 0));
	
	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Transform>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(1.f, -2.f, 1.f));
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).SetAll(0.1f);
	

	ECS::Create(2);
	ECS::Add<Mesh>(2);
	ECS::Add<Transform>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(-5.f, -2.f, 0.f));
	ECS::Get<Mesh>(2).LoadOBJ("Models/monkey.obj", glm::vec4(0.01f, 1.0f, 0.01f, 1.0f));
	ECS::Add<Material>(2);
	ECS::Get<Material>(2).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(2).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(2).SetAll(0.1f);

	
	
	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Transform>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(-5.f, -5.f, -5.f));
	ECS::Get<Mesh>(3).LoadOBJ("Models/monkey.obj", glm::vec4(0.1f, 0.1f, 1.0f, 1.0f));
	ECS::Add<Material>(3);
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/help.jpg");
	ECS::Get<Material>(3).SetAll(0.1f);


	
	
	ECS::Create(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Transform>(4);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(2.f, -10.f, 5.f));
	ECS::Get<Mesh>(4).LoadOBJ("Models/earth.obj", glm::vec4(0.1f, 0.5f, 0.5f, 1.0f));
	ECS::Add<Material>(4);
	ECS::Get<Material>(4).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(4).LoadSpecularFromFile("images/help.jpg");
	ECS::Get<Material>(4).SetAll(0.1f);

		
	ECS::Create(5);
	ECS::Add<Mesh>(5);
	ECS::Add<Transform>(5);
	ECS::Get<Transform>(5).SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	ECS::Get<Mesh>(5).SetVAO(ECS::Get<Mesh>(1).GetVAO());
	
	ECS::Create(6);
	ECS::Add<Mesh>(6);
	ECS::Add<Transform>(6);
	ECS::Get<Transform>(6).SetPosition(glm::vec3(0.f, -11.5f, 0.f));
	ECS::Add<Material>(6);
	ECS::Get<Mesh>(6).LoadOBJ("Models/Temple.obj", glm::vec4(1.f,1.f,1.f,1.f));
	ECS::Get<Material>(6).LoadDiffuseFromFile("Images/trappin.JPG");
	ECS::Get<Material>(6).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(6).SetAll(0.1f);




}

void Scene::Update()
{
	
}