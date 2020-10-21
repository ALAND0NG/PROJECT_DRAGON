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

	//ECS::AttachRegistry(&m_Reg);


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
		glm::vec3 posTemp = ECS::Get<Camera>(0).GetPosition();

		posTemp += ECS::Get<Camera>(0).GetForward() * 3.f * Timer::dt;

		ECS::Get<Camera>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Camera>(0).GetPosition();
		posTemp -= ECS::Get<Camera>(0).GetForward() * 3.f * Timer::dt;
		ECS::Get<Camera>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Camera>(0).GetPosition();
		posTemp += glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp())) * 3.f * Timer::dt;


		ECS::Get<Camera>(0).SetPosition(posTemp);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 posTemp = ECS::Get<Camera>(0).GetPosition();
		posTemp -= glm::normalize(glm::cross(ECS::Get<Camera>(0).GetForward(), ECS::Get<Camera>(0).GetUp())) * 3.f * Timer::dt;


		ECS::Get<Camera>(0).SetPosition(posTemp);
	}
}

void Game::GameLoop() //Main update function
{
	while (!m_Close)
	{
		//This is the main update function
		Timer::Tick();

		GameInput();

		BackEnd::Update();

		m_ActiveScene->Update(); //Scene specific update
	}
}
