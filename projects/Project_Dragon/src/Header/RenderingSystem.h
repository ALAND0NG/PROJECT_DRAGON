#pragma once
#include <Header/Shader.h>
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
#include <header/Timer.h>
#include <header/Texture2D.h>
#include <header/Texture2DData.h>
#include "GLFW/glfw3.h"
#include <glad/glad.h>

static class RenderingSystem
{
public:
	static void Init();
	static void Update();
private:
	static Shader::sptr shader;
	static void ECSUpdate(); //Goes through any ECS component that needs a frame by frame update, and applies that
};