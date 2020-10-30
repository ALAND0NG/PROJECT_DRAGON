#include <Header/TankScene.h>

void TankScene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);

	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(2.f, 0.f, 0.f));
	ECS::Add<Camera>(0);

	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Transform>(1);
	ECS::Add<PhysicsBody>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(0.f, 0.f, 0.f));
	ECS::Get<PhysicsBody>(1).SetBox(ECS::Get<Transform>(1).GetPosition(), 2.f, 2.f, 2.f);
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Get<PhysicsBody>(1).SetMass(1.f);
	ECS::Get<PhysicsBody>(1).SetFriction(0.1f);
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadDiffuse2FromFile("images/sample.png"); //used for texture blending
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).Tex1Str = 1.f;
	ECS::Get<Material>(1).Tex2Str = 0.f;
	ECS::Get<Material>(1).SetAll(1.f);

	ECS::Create(2);
	ECS::Add<Transform>(2);
	ECS::Add<LightSource>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(0.f, 3.f, 0.f));

	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Transform>(3);
	ECS::Add<PhysicsBody>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(5.f, 0.f, 0.f));
	ECS::Get<PhysicsBody>(3).SetMass(1.f);
	ECS::Get<PhysicsBody>(3).SetFriction(0.01f);
	ECS::Get<PhysicsBody>(3).SetBox(ECS::Get<Transform>(1).GetPosition(), 2.f, 2.f, 2.f);
	ECS::Get<Mesh>(3).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Add<Material>(3);
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(3).LoadDiffuse2FromFile("images/sample.png"); //used for texture blending
	ECS::Get<Material>(3).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(3).Tex1Str = 1.f;
	ECS::Get<Material>(3).Tex2Str = 1.f;
	ECS::Get<Material>(3).SetAll(1.f);



	
}

void TankScene::Update()
{
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3 (10, 0.f, 0.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_K) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3(-10.0f, 0.f, 0.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_J) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3(0.0f, 10.f, 0.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_L) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3(0.0f, -10.f, 0.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_U) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3(0.0f, 0.0f, 10.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_O) == GLFW_PRESS)
	{
		ECS::Get<PhysicsBody>(1).ApplyForce(glm::vec3(0.0f, -0.0f, -10.f));
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_F) == GLFW_PRESS)
	{
		ECS::Get<Transform>(1).SetPosition(glm::vec3(2.f, 2.f, 2.f));
	}



}

