#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>
#include "Camera.h"
#include "Scene/Scene.h"
#include "Scene/TestScene.h"

class Game
{
public:

	void Init();
	void Tick();
	void Update();
	GLFWwindow* GetWindow();
	float GetdeltaTime();
	void KeyInput();
	void AttachRegistry();


private:

	bool windowShouldClose = false;
	float m_deltaTime;
	float m_previousTime;
	GLFWwindow* m_window;
	entt::registry* m_registry; //the main reg
	Scene* m_ActiveScene;

	std::vector<Scene*> m_scenes;
	


};