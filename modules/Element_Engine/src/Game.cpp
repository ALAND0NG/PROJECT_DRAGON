#include "Game.h"
#include <iostream>
#include <string>


Game::Game()
{
	
}

Game::~Game()
{
}

void Game::InitGame(int scene_index)
{
	BackEnd::Init();
	
	m_ActiveScene = m_Scenes[scene_index];

	m_ActiveScene->InitScene();

	




	GameLoop(); //kicks the gameloop into starting



}

void Game::AddScene(Scene* scene)
{
	m_Scenes.push_back(scene);
}

void Game::GameInput()
{
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();

		//posTemp.x += ECS::Get<Camera>(0).GetForward().x * 8.f * Timer::dt;
		//posTemp.z += ECS::Get<Camera>(0).GetForward().z * 8.f * Timer::dt;


		//ECS::Get<Transform>(0).SetPosition(posTemp);
	

		float x = ECS::Get<Camera>(0).GetForward().x;
		float z = ECS::Get<Camera>(0).GetForward().z;


		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(x * 5.f, 0, z *5.f));


	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		/*
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp.x -= ECS::Get<Camera>(0).GetForward().x * 8.f * Timer::dt;
		posTemp.z -= ECS::Get<Camera>(0).GetForward().z * 8.f * Timer::dt;

		ECS::Get<Transform>(0).SetPosition(posTemp);
		*/

		float x = ECS::Get<Camera>(0).GetForward().x;
		float z = ECS::Get<Camera>(0).GetForward().z;


		
		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(-x * 5.f, 0, -z*5.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		
		//glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		glm::vec3 direction = glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(direction.x*5, direction.y*5, direction.z*5));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 direction = -glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(direction.x*5, direction.y*5, direction.z*5));
		
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		/*
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp.y = 15.f;
		ECS::Get<Transform>(0).SetPosition(posTemp);
		*/
	//	ECS::Get<PhysicsBody>(0).GetBody()->setActivationState(1);
		//ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(0, 10, 0));
		ECS::Get<Player>(0).CheckJump();

		if (ECS::Get<Player>(0).GetPlayerData().m_CanJump)
		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(0, 10, 0));
	}
	


}

void Game::GameLoop() //Main update function
{
	while (!glfwWindowShouldClose(BackEnd::m_Window))
	{
		Timer::Tick();

		GameInput();

		BackEnd::Update();

		m_ActiveScene->Update(); //Scene specific update
	}
	Logger::Uninitialize();
}
