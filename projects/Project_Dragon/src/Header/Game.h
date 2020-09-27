#pragma once
#include "entt.hpp"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "Header/ECS.h"

//main game class
class Game
{
public:
	Game();
	~Game();

	void InitGame();
	
	void GameInput(); //All input functions go in here

	void GameLoop(); //this is the core update function

	void Tick()//Gives us a deltaTime
	{
		float time = static_cast<float>(glfwGetTime());
		m_deltaTime = time - m_prevTime;
		m_prevTime = time;
	}

private:
	//We want the registry to be here, and all other instances to be a pointer to here
	//This class will have most of the main game functions, such as input, rendering
	//They will however be abstracted to some other classes to make an ECS based game
	//cleaner and easier to code
	entt::registry m_Reg;
	
	//we also want the main window to be here
	GLFWwindow* m_Window;

	float m_deltaTime; //time between current frame and previous

	float m_prevTime;
	
	bool m_Close = false; //tells us if we should close the window

};