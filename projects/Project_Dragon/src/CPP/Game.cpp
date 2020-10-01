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

	ecs.AttachRegistry(&m_Reg);

	InitWindow(1000, 1000, "Project Dragon");

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
		//This is the main update function
		Tick();

		GameInput();

		m_ActiveScene->Update(); //Scene specific update
		
		Draw();

	}
}

void Game::InitWindow(float width, float height, std::string name)
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW init failed!" << std::endl;
		throw std::runtime_error("GLFW init failed!");
	}


	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);


	glfwWindowHint(GLFW_RESIZABLE, true);

	m_Window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);


	glfwMakeContextCurrent(m_Window);

	//This initializes OpenGL via GLAD.
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Glad init failed!" << std::endl;
		throw std::runtime_error("Glad init failed!");
	}

	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(m_Window);
}
