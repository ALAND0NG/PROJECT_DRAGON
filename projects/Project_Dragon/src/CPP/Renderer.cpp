#include <Header/Renderer.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>



void Renderer::Init(GLFWwindow* window)
{
	//for now this is a test
	static const float points[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	static const float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	vbo = VertexBuffer::Create();
	vbo->LoadData(points, 9);
	VertexBuffer::sptr color_vbo = VertexBuffer::Create();
	color_vbo->LoadData(colors, 9);

	 vao = VertexArrayObject::Create();
	vao->AddVertexBuffer(vbo, {
		BufferAttribute(0, 3, GL_FLOAT, false, 0, NULL)
		});
	vao->AddVertexBuffer(color_vbo, {
		BufferAttribute(1, 3, GL_FLOAT, false, 0, NULL)
		});

	// Load our shaders
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();


	camera = Camera::Create();
	camera->SetPosition(glm::vec3(0, 1, -1));
	camera->LookAt(glm::vec3(0.0f));

	

}

void Renderer::Draw(GLFWwindow* window)
{	
	double thisFrame = glfwGetTime();

	// Our high-precision timer
	float dt = static_cast<float>(thisFrame - lastFrame);

	transform = glm::rotate(glm::mat4(1.0f), static_cast<float>(thisFrame), glm::vec3(0, 0, 1));

	shader->Bind();

	shader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vao->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao->UnBind();

	glfwSwapBuffers(window);
}