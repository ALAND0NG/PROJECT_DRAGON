#pragma once
#include <Shader.h>
#include <VertexArrayObject.h>
#include <MeshFactory.h>
#include <indexbuffer.h>
#include <VertexBuffer.h>
#include <MeshBuilder.h>
#include <NotObjLoader.h>
#include <VertexTypes.h>
#include <Shader.h>
#include <Camera.h>
#include <ECS.h>
#include <Timer.h>
#include <Texture2D.h>
#include <Texture2DData.h>
#include "GLFW/glfw3.h" 
#include <glad/glad.h>

static class RenderingSystem
{
public:
	static void Init();
	static void Update();
	static Shader::sptr GetShader()
	{
		return shader;
	}
private:
	//regular mesh shader
	static Shader::sptr shader;
	static Shader::sptr AnimationShader;
	static Shader::sptr BlendShader;
	static Shader::sptr UIShader;
	static void ECSUpdate(); //Goes through any ECS component that needs a frame by frame update, and applies that
};