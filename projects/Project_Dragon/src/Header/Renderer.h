#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLM/glm.hpp>
#include <Header/Shader.h>
#include <Header/VertexArrayObject.h>
#include <Header/VertexBuffer.h>
#include <Header/ECS.h>

class Renderer
{
public:
	void Init(GLFWwindow* window);
	void Draw(GLFWwindow* window);
private:
	Shader::sptr shader;
	VertexBuffer::sptr vbo;
	VertexArrayObject::sptr vao;

	// Our high-precision timer
	double lastFrame = glfwGetTime();

	ECS* ecs;

	Camera::sptr camera;


	glm::mat4 transform = glm::mat4(1.0f);
};