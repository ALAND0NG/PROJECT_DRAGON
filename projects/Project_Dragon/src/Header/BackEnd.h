#pragma once
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <string>
//This just helps keep the code much cleaner

class BackEnd
{
public:
	BackEnd()
	{
		m_Window = nullptr;
	}

	void Init(float width, float height, std::string name);

	GLFWwindow* GetWindow()
	{
		return m_Window;
	}
private:
	GLFWwindow* m_Window;
};