#pragma once
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include <Header/VertexArrayObject.h>
#include <Header/MeshFactory.h>
#include <Header/indexbuffer.h>
#include <Header/VertexBuffer.h>
#include <Header/MeshBuilder.h>
#include <Header/NotObjLoader.h>
#include <Header/VertexTypes.h>
#include <Header/Shader.h>
#include <header/Camera.h>
#include <Header/ECS.h>

class BackEnd
{
public:
	static void Init();
	static void Update();//Called once per frame, goes through all entities and does whatever is required per component

	static Shader::sptr shader;

	static GLFWwindow* m_Window;
private:
	static void InitWindow();


};