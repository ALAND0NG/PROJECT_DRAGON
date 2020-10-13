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

}

void Game::GameLoop() //mainly updates the game
{
	while (!m_Close)
	{
		//This is the main update function
		Tick();

		GameInput();

		BackEnd::Update();

		m_ActiveScene->Update(); //Scene specific update

	}
}
