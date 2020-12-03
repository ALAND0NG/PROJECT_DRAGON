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
	float verticalVelo = ECS::Get<PhysicsBody>(0).GetBody()->getVelocityInLocalPoint(btVector3(0, 0, 0)).getY();
	float movementSpeed = ECS::Get<Player>(0).GetMovementSpeed();

	/*
	//walking forward and strafing left
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		btVector3 finalMovement;

		float x = ECS::Get<Camera>(0).GetForward().x;
		float z = ECS::Get<Camera>(0).GetForward().z;

		finalMovement = btVector3(x * movementSpeed, verticalVelo, z * movementSpeed); //forward vector
		glm::vec3 direction = glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));
		finalMovement += BtToGlm::GLMTOBTV3(direction);

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(finalMovement);

	}
	*/
	//Sprint
	if (glfwGetKey(BackEnd::m_Window, GLFW_MOD_SHIFT) == GLFW_PRESS)
	{
		ECS::Get<Player>(0).SetMovementSpeed(15.f);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_MOD_SHIFT) == GLFW_RELEASE)
	{
		ECS::Get<Player>(0).SetMovementSpeed(10.f);
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{

		float x = ECS::Get<Camera>(0).GetForward().x;
		float z = ECS::Get<Camera>(0).GetForward().z;

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(x * movementSpeed, verticalVelo, z * movementSpeed));

	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		float x = ECS::Get<Camera>(0).GetForward().x;
		float z = ECS::Get<Camera>(0).GetForward().z;
		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(-x * movementSpeed, verticalVelo, -z* movementSpeed));
	}


	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 direction = glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(direction.x* movementSpeed, verticalVelo, direction.z* movementSpeed));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 direction = -glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));

		

		ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(direction.x* movementSpeed, verticalVelo, direction.z* movementSpeed));
		
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

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
