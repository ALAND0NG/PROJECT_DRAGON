#include <BackEnd.h>
#include <PhysicsSystem.h>
#include <iostream>
#include <AssetLoader.h>
#include <AudioEngine.h>

GLFWwindow* BackEnd::m_Window = glfwCreateWindow(1920, 1080, "The funny game", nullptr, nullptr); //Initializing outside of class because its a static

int BackEnd::m_WindowHeight = 0;
int BackEnd::m_WindowWidth = 0;
// ^^ same comment

void mouse_Callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void BackEnd::Init()
{
	Logger::Init();
	InitWindow();
	RenderingSystem::Init();
	PhysicsSystem::Init();
	IMGUIManager::Init();
	AssetLoader::Init();
	SpriteRenderer::initRenderData();
	SoundManager::init("", 512);

	glEnable(GL_DEPTH_TEST);
}
bool spacePressed = false;
bool currentType = true;

void BackEnd::Update()
{
	glClearColor(0.53f, 0.81f, 0.93f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PhysicsSystem::Update();
	RenderingSystem::Update();
	IMGUIManager::Update();
	
	glfwSwapBuffers(BackEnd::m_Window);
	glfwPollEvents();
}

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	ECS::Get<Camera>(0).ResizeWindow(width, height);
}

void window_close_callback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, GLFW_FALSE);
}

void BackEnd::InitWindow()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW init failed!" << std::endl;
		throw std::runtime_error("GLFW init failed!");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, true);

	BackEnd::m_Window = glfwCreateWindow(1920, 1080, "Project Dragon", nullptr, nullptr);

	BackEnd::m_WindowHeight = 1080;
	BackEnd::m_WindowWidth = 1920;

	glfwMakeContextCurrent(BackEnd::m_Window);

	//glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	
	glfwSetWindowSizeCallback(BackEnd::m_Window, GlfwWindowResizedCallback);
	glfwSetCursorPosCallback(BackEnd::m_Window, mouse_Callback);
	glfwSetMouseButtonCallback(BackEnd::m_Window, mouse_button_callback);

	//This initializes OpenGL via GLAD.
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "Glad init failed!" << std::endl;
		throw std::runtime_error("Glad init failed!");
	}

	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 0.0);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 90.0f;

void mouse_Callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = -0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw -= xoffset;
	pitch -= yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	ECS::Get<Camera>(0).SetForward(glm::normalize(front));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (ECS::Get<Player>(0).FireWeapon(0))
			std::cout << "Hit an enemy\n";
	}
}