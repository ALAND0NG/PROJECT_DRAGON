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
