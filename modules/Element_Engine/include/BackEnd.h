#pragma once
#include <RenderingSystem.h>
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include <IMGUIManager.h>

class BackEnd
{
public:
	static void Init();
	static void Update();//Called once per frame, goes through all entities and does whatever is required per component

	static GLFWwindow* m_Window;
private:
	static void InitWindow();
	static int m_aspectRatio;
	static int m_WindowWidth;
	static int m_WindowHeight;


};