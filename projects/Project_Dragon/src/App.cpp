#include "App.h"

void App::Init()
{
	//init GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 1;
	}
	//create GLFW window
	m_window = glfwCreateWindow(800, 600, "THE FUNNY APPLICATION!!!!!!", nullptr, nullptr);
	//want gl commands to be execuited for our window
	glfwMakeContextCurrent(m_window);
	

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 2;
	}
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

}

void App::Tick()
{

	float time = static_cast<float>(glfwGetTime());
	m_deltaTime = time - m_previousTime;
	m_previousTime = time;
}

void App::Update()
{
	//this is the main update function
	while (!glfwWindowShouldClose(m_window))
	{
		Tick();
		
		glfwPollEvents();
		
		glClearColor(1.0f, 0.5f, 0.1f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(m_window);

	}
}