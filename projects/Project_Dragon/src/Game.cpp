#include "Game.h"

void Game::Init()
{
	//manually set the active scene here
	m_scenes.push_back(new TestScene());
	m_ActiveScene = m_scenes[0];
	m_ActiveScene->InitScene();
	m_window = m_ActiveScene->GetWindow();

}

void Game::Tick()
{

	float time = static_cast<float>(glfwGetTime());
	m_deltaTime = time - m_previousTime;
	m_previousTime = time;
}

void Game::Update()
{
	//this is the main update function
	while (m_ActiveScene->GetClose() == 0)
	{
		Tick();

		//this is the active scene's update function
		m_ActiveScene->OnUpdate();

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(GetWindow());

	}
}

GLFWwindow* Game::GetWindow()
{
	return m_window;
}

float Game::GetdeltaTime()
{
	return m_deltaTime;
}

//void Game::KeyInput()
//{
	/*
	//this is the basic camera/player movement movement
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_camera.ProcessKeyboard(FORWARD, m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_camera.ProcessKeyboard(BACKWARD, m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_camera.ProcessKeyboard(LEFT, m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_camera.ProcessKeyboard(RIGHT, m_deltaTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS)
		std::cout << m_camera.Position.x << std::endl << m_camera.Position.y << std::endl << m_camera.Position.z;
	*/		
//}



