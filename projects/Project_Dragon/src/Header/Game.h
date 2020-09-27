#pragma once
#include "entt.hpp"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "Header/Scene.h"
#include "Header/BackEnd.h"
//main game class
class Game
{
public:
	Game();
	~Game();

	void InitGame(); //Initializes all the stuff
	
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
	//This class will have most of the main game functions, such as input,
	//They will however be abstracted to some other classes to make an ECS based game
	//cleaner and easier to code
	entt::registry m_Reg;
	
	//we also want the main window to be here
	GLFWwindow* m_Window = nullptr;

	float m_deltaTime = NULL; //time between current frame and previous

	float m_prevTime = NULL;
	
	bool m_Close = false; //tells us if we should close the window

	ECS ecs; //The main ECS, contains a vector with all the entities

	BackEnd m_Backend; //main backend

	std::vector<Scene*> m_Scenes;
	Scene* m_ActiveScene;
};