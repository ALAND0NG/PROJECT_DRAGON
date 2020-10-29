#pragma once
#include <Header/RenderingSystem.h>
#include "GLFW/glfw3.h"
#include <glad/glad.h>


class BackEnd
{
public:
	static void Init();
	static void Update();//Called once per frame, goes through all entities and does whatever is required per component

	static GLFWwindow* m_Window;
private:
	static void InitWindow();


};