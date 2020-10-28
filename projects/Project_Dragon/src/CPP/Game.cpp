#include "Header/Game.h"
#include <iostream>
#include <string>


Game::Game()
{
	
}

Game::~Game()
{
}

void Game::InitGame()
{

	BackEnd::Init();

	m_Scenes.push_back(new Scene());

	m_ActiveScene = m_Scenes[0];

	m_ActiveScene->InitScene();

	GameLoop(); //kicks the gameloop into starting



}

void Game::GameInput()
{
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();

		posTemp.x += ECS::Get<Camera>(0).GetForward().x * 8.f * Timer::dt;
		posTemp.z += ECS::Get<Camera>(0).GetForward().z * 8.f * Timer::dt;
		

		ECS::Get<Transform>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp.x -= ECS::Get<Camera>(0).GetForward().x * 8.f * Timer::dt;
		posTemp.z -= ECS::Get<Camera>(0).GetForward().z * 8.f * Timer::dt;
		
		ECS::Get<Transform>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp += glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp())) * 8.f * Timer::dt;
		

		ECS::Get<Transform>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp -= glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp())) * 8.f * Timer::dt;
		

		ECS::Get<Transform>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Transform>(0).GetPosition();
		posTemp.y = -9.f;
		ECS::Get<Transform>(0).SetPosition(posTemp);
	}

}

void Game::GameLoop() //Main update function
{
	while (!m_Close)
	{
		Timer::Tick();

		GameInput();

		BackEnd::Update();

		m_ActiveScene->Update(); //Scene specific update
	}
}
