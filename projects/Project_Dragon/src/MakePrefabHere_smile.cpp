#include "MakePrefabHere_smile.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <AssetLoader.h>

void PrefabMakeScene::InitScene()
{
	//Player Camera - - - Need This For A Game To Run
	m_sceneReg = new entt::registry;
	ECS::AttachRegistry(m_sceneReg);


	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Add<PhysicsBody>(0);
	ECS::Add<Camera>(0);
	ECS::Add<Player>(0);
	ECS::Get<Camera>(0).ResizeWindow(1920, 1080);
	ECS::Get<PhysicsBody>(0).AddBody(15, btVector3(3, 100, 3), btVector3(1, 2, 1));
	ECS::Add<LightSource>(0);
	ECS::Get<PhysicsBody>(0).m_Entity = 0;


	//plane so camera doesn't fall

	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Material>(1);
	ECS::Add<Transform>(1);
	ECS::Add<PhysicsBody>(1);
	ECS::Add<LightSource>(1);
	ECS::Get<Mesh>(1).LoadOBJ("models/other/plane.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Transform>(1).SetScale(glm::vec3(10000.f, 1.f, 10000.f));
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).SetAll(1.f);
	ECS::Get<PhysicsBody>(1).AddBody(0.f, btVector3(0, 0, 0), btVector3(10000, 0, 100000));
	ECS::Get<PhysicsBody>(1).m_Entity = 1;




}

void PrefabMakeScene::Update()
{
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_G) == GLFW_PRESS)
	{
		glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	
	/*
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_1) == GLFW_PRESS)
		ECS::Get<MorphAnimator>(2).SetActiveAnimation(0);


	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_2) == GLFW_PRESS)
		ECS::Get<MorphAnimator>(2).SetActiveAnimation(1);

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_3) == GLFW_PRESS)
		ECS::Get<MorphAnimator>(2).SetActiveAnimation(2);
	*/
}
