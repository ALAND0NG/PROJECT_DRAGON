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

	//m_Scenes.push_back(new Scene());
	m_Scenes.push_back(new TankScene());

	m_ActiveScene = m_Scenes[0];

	m_ActiveScene->InitScene();



	GameLoop(); //kicks the gameloop into starting



}

void Game::GameInput()
{
	//For actual game, input will be handled here
	//for the CG midterm, I will simply do it in the scene specific update function

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
