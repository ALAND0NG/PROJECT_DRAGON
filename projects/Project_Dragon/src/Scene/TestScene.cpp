#include "TestScene.h"     

void TestScene::InitScene()
{	
	m_SceneReg = new entt::registry;

	//init GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 1;
	}
	//create GLFW window
	m_Scenewindow = glfwCreateWindow(800, 600, "THE FUNNY APPLICATION!!!!!!", NULL, NULL);

	//want gl commands to be execuited for our window
	glfwMakeContextCurrent(m_Scenewindow);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Failed to initialize Glad" << std::endl;
		//return 2;
	}
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	auto test = CreateEntity("TestEntity");
	test.AddComponent<TestComponent>("TestEntity");
	
	m_testEnt = test;

	

	/*
	 //Example entity creation
	auto testEntity = m_SceneReg->create();

	AddComponent<TestComponent>(testEntity); //Example add component
	
	Get<TestComponent>(testEntity).testInt = 1; //Example get component
	
	std::cout << Get<TestComponent>(testEntity).testInt;
	*/

}

void TestScene::OnUpdate()
{
	m_testEnt.GetComponent<TestComponent>().TestPrint();
}