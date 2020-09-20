#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main() 
{
	//init GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		return 1;
	}
	//create GLFW window
	GLFWwindow* window = glfwCreateWindow(300, 300, "100743060", nullptr, nullptr);
	//want gl commands to be execuited for our window
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		return 2;
	}
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
