#include <Header/BackEnd.h>
#include <iostream>

GLFWwindow* BackEnd::m_Window = glfwCreateWindow(800, 800, "The funny game", nullptr, nullptr);

void BackEnd::Init()
{
	InitWindow();
}

void BackEnd::Update()
{
	
	glfwPollEvents();
	glClearColor(0.08f, 0.17f, 0.31f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(BackEnd::m_Window);

}

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void BackEnd::InitWindow()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW init failed!" << std::endl;
		throw std::runtime_error("GLFW init failed!");
	}

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

	glfwWindowHint(GLFW_RESIZABLE, true);

	BackEnd::m_Window = glfwCreateWindow(800, 800, "The funny game", nullptr, nullptr);

	glfwMakeContextCurrent(BackEnd::m_Window);

	glfwSetWindowSizeCallback(BackEnd::m_Window, GlfwWindowResizedCallback);

	//This initializes OpenGL via GLAD.
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Glad init failed!" << std::endl;
		throw std::runtime_error("Glad init failed!");
	}

	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
