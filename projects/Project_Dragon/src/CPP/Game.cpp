#include "Header/Game.h"
#include <iostream>


Game::Game()
{
}

Game::~Game()
{
}

void Game::InitGame()
{

	ecs.AttachRegistry(&m_Reg);

	m_Backend.Init(1000, 1000, "Project Dragon");

	m_Window = m_Backend.GetWindow();

	m_Scenes.push_back(new Scene(&ecs));

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
		Tick();

		GameInput();

		m_ActiveScene->Update();
		
		//This is the main update function
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);

	}
}
