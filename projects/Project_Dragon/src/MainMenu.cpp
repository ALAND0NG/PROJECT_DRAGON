#include "MainMenu.h"

void MainMenu::InitScene()
{

	m_sceneReg = new entt::registry;
	ECS::AttachRegistry(m_sceneReg);


	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Add<PhysicsBody>(0);
	ECS::Add<Camera>(0);
	ECS::Add<Player>(0);
	ECS::Add<UI>(0);
	ECS::Add<Menu>(0);
	ECS::Get<UI>(0).mesh.LoadOBJ("models/other/plane.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<UI>(0).material.LoadDiffuseFromFile("images/MainMenu.png");
	ECS::Get<UI>(0).material.LoadSpecularFromFile("images/UIGood.png");
	ECS::Get<UI>(0).material.SetAll(1.f);
	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);
	ECS::Get<PhysicsBody>(0).AddBody(100, btVector3(3, 10, 3), btVector3(1, 2, 1), 3.0f);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;


}

void MainMenu::Update()
{
}
