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
//big pragmaregion for windowcreation to not take up too much space	
#pragma region windowcreation
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW init failed!" << std::endl;
		throw std::runtime_error("GLFW init failed!");
	}

	
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

	
	glfwWindowHint(GLFW_RESIZABLE, true);

	m_Window = glfwCreateWindow(800, 600, "Project Dragon", nullptr, nullptr);

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
	#pragma endregion

//temporary test here
	
	ecs.AttachRegistry(&m_Reg);

	ecs.Create(0); //here the 0 is the id

	ecs.Add<TestComponent>(0);

	



	GameLoop();

}

void Game::GameInput()
{

}

void Game::GameLoop()
{
	while (!m_Close)
	{
		std::cout << ecs.Get<TestComponent>(0).lol;

		//This is the main update function
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);

	}
}
