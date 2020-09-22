#include "TestScene.h"

void TestScene::InitScene(float windowWidth, float windowHeight)
{
	//init GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 1;
	}
	//create GLFW window
	m_Scenewindow = glfwCreateWindow(windowWidth, windowHeight, "THE FUNNY APPLICATION!!!!!!", NULL, NULL);

	//want gl commands to be execuited for our window
	glfwMakeContextCurrent(m_Scenewindow);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 2;
	}
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	
	m_SceneReg = new entt::registry;

	Entity testEnt(CreateEntity());
	
	Add<TransformComponent>(testEnt.GetHandle());
	
	

}

void TestScene::OnUpdate()
{

}
