#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class App
{
public:
	void Init();
	void Tick();
	void Update();
private:
	float m_deltaTime;
	float m_previousTime;
	GLFWwindow* m_window;
};