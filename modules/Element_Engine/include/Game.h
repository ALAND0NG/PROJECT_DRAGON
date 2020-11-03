#pragma once
#include "entt.hpp"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "Scene.h"
#include "TankScene.h"
#include <BackEnd.h>
#include <Timer.h>



//main game class
class Game
{
public:
	Game();
	~Game();

	void InitGame(); //Initializes all the stuff

	void GameInput(); //All input functions go in here

	void GameLoop(); //this is the core update function

	//void InitWindow(float width, float height, std::string name);





	//void Tick()//Gives us a deltaTime
//	{
	//	float time = static_cast<float>(glfwGetTime());
	//	m_deltaTime = time - m_prevTime;
	//	m_prevTime = time;
	//}
//


private:

	//float m_deltaTime = NULL; 

	//float m_prevTime = NULL;

	bool m_Close = false; 

	

	std::vector<Scene*> m_Scenes;
	Scene* m_ActiveScene = NULL;

};