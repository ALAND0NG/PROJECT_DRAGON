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
	btVector3 movement = btVector3(0, 0, 0);
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
		ECS::Get<Player>(0).SetMovementSpeed(25.f);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_MOD_SHIFT) == GLFW_RELEASE)
	{
		ECS::Get<Player>(0).SetMovementSpeed(10.f);
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		movement.setX(movement.getX() + ECS::Get<Camera>(0).GetForward().x * 1.8);
		movement.setZ(movement.getZ() + ECS::Get<Camera>(0).GetForward().z * 1.8);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		movement.setX(movement.getX() - ECS::Get<Camera>(0).GetForward().x * 1.8);
		movement.setZ(movement.getZ() - ECS::Get<Camera>(0).GetForward().z * 1.8);
	}

	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 direction = glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));
		movement.setX(movement.getX() + direction.x * 1.8);
		movement.setZ(movement.getZ() + direction.z * 1.8);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 direction = -glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp()));
		movement.setX(movement.getX() + direction.x * 1.8);
		movement.setZ(movement.getZ() + direction.z * 1.8);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		ECS::Get<Player>(0).CheckJump();

		//if (ECS::Get<Player>(0).GetPlayerData().m_CanJump)
			verticalVelo = 22.f;
	}

	if (m_SceneIndex == 0)
		if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_ENTER) == GLFW_PRESS)
			SwitchScene(1);
	if (m_SceneIndex == 2)
		if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_ENTER) == GLFW_PRESS)
			SwitchScene(0);

	//check to see if player died
	if (ECS::Get<Player>(0).GetPlayerData().m_HP == 0 && m_SceneIndex == 1)
		SwitchScene(2);



	ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(movement.getX() * movementSpeed, verticalVelo, movement.getZ() * movementSpeed));
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

void Game::SwitchScene(int SceneIndex)
{
	PhysicsSystem::ClearWorld();
	ECS::DestroyAllEntities();
	m_SceneIndex = SceneIndex;
	m_ActiveScene = m_Scenes[SceneIndex];
	m_ActiveScene->InitScene();

}