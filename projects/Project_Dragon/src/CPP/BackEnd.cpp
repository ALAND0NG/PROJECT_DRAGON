#include <Header/BackEnd.h>
#include <iostream>

GLFWwindow* BackEnd::m_Window = glfwCreateWindow(800, 800, "The funny game", nullptr, nullptr); //Initializing outside of class because its a static

Shader::sptr BackEnd::shader = nullptr; // ^^ same comment

void mouse_Callback(GLFWwindow* window, double xpos, double ypos);

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

void BackEnd::Init()
{
	Logger::Init();
	
	InitWindow();

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("shader/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.3f;
	float     lightSpecularPow = 5.0f;
	glm::vec3 ambientCol = glm::vec3(0.1f, 0.1f, 0.1f);
	float     ambientPow = 0.1f;
	float     shininess = 4.0f;

	
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

}
bool spacePressed = false;
bool currentType = true;
void BackEnd::Update()
{
	glClearColor(0.00f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	
	lightPos = ECS::Get<Transform>(5).GetPosition();

	shader->SetUniform("u_LightPos", lightPos);

	ECS::Get<Transform>(1).SetRotation(glm::vec3(0, 1, 0), 2 * Timer::dt);
	ECS::Get<Transform>(2).SetRotation(glm::vec3(1, 0, 0), 5 * Timer::dt);
	
	
	//here we need to take all entities with components that need to be passed to the shaders
	//just automates this code here
	
	auto reg = ECS::GetReg();

	for (int i = 0; i < reg->size(); i++)
	{
		if (ECS::Has<Transform>(i) == true && ECS::Has<Mesh>(i) == true)
		{
			ECS::Get<Transform>(i).ComputeGlobalMat();
			
			shader->Bind();
			//I know that I could properly get the camera, but as a convention we will simply always declare it as entity 0 to avoid coding an entity
			//identitifier
			shader->SetUniformMatrix("u_ModelViewProjection", ECS::Get<Camera>(0).GetViewProjection() * ECS::Get<Transform>(i).GetTransform());
			shader->SetUniformMatrix("u_Model", ECS::Get<Transform>(i).GetTransform());
			shader->SetUniformMatrix("u_ModelRotation", glm::toMat3(ECS::Get<Transform>(i).GetRotation()));
			shader->SetUniform("u_CamPos", ECS::Get<Camera>(0).GetPosition());
			ECS::Get<Mesh>(i).GetVAO()->Render();
		}
	}
	
	glfwSwapBuffers(BackEnd::m_Window);
	glfwPollEvents();

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

	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

	glfwWindowHint(GLFW_RESIZABLE, true);

	BackEnd::m_Window = glfwCreateWindow(800, 800, "The funny game", nullptr, nullptr);

	glfwMakeContextCurrent(BackEnd::m_Window);

	glfwSetInputMode(BackEnd::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowSizeCallback(BackEnd::m_Window, GlfwWindowResizedCallback);
	glfwSetCursorPosCallback(BackEnd::m_Window, mouse_Callback);

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

	float sensitivity = 0.1f; // change this value to your liking
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