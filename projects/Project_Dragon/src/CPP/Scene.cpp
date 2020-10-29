#include "Header/Scene.h"

void Scene::InitScene()
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegistry(m_sceneReg);
	
	ECS::Create(0); //please please please always have camera be entity 0 it will break otherwise
	ECS::Add<Transform>(0);
	ECS::Get<Transform>(0).SetPosition(glm::vec3(0.f, 0.f, 0.f));
	ECS::Add<Camera>(0);
	
	ECS::Create(1);
	ECS::Add<Mesh>(1);
	ECS::Add<Transform>(1);
	ECS::Get<Transform>(1).SetPosition(glm::vec3(1.f, -9.f, 1.f));
	ECS::Get<Mesh>(1).LoadOBJ("Models/cube.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Add<Material>(1);
	ECS::Get<Material>(1).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(1).LoadDiffuse2FromFile("images/sample.png"); //used for texture blending
	ECS::Get<Material>(1).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(1).Tex1Str = 1.f;
	ECS::Get<Material>(1).Tex2Str = 1.f;
	ECS::Get<Material>(1).SetAll(1.f);

	ECS::Create(2);
	ECS::Add<LightSource>(2);
	ECS::Add<Transform>(2);
	ECS::Get<Transform>(2).SetPosition(glm::vec3(5.f, -9.f, 5.f));

	
	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Transform>(3);
	ECS::Add<Material>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(5.f, -11.f, 0.f));
	ECS::Get<Transform>(3).SetScale(glm::vec3(10.f, 10.f, 10.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/plane.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(3).LoadDiffuse2FromFile("images/trappin.jpg");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(3).Tex1Str = 1.f;
	ECS::Get<Material>(3).Tex2Str = 0.f;
	ECS::Get<Material>(3).SetAll(0.1f);

	ECS::Create(4);
	ECS::Add<LightSource>(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Transform>(4);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(5.f, -9.f, 5.f));
}
glm::vec3 tempVec;
void Scene::Update()
{
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_J) == GLFW_PRESS)
	{
		//move object demo
		tempVec = ECS::Get<Transform>(2).GetPosition();
		tempVec.x += 5.f * Timer::dt;
		ECS::Get<Transform>(2).SetPosition(tempVec);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_L) == GLFW_PRESS)
	{
		//move object demo
		tempVec = ECS::Get<Transform>(4).GetPosition();
		tempVec.x += 5.f * Timer::dt;
		ECS::Get<Transform>(4).SetPosition(tempVec);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_I) == GLFW_PRESS)
	{
		//move object demo
		tempVec = ECS::Get<Transform>(4).GetPosition();
		tempVec.z -= 5.f * Timer::dt;
		ECS::Get<Transform>(4).SetPosition(tempVec);
	}
	if (glfwGetKey(BackEnd::m_Window, GLFW_KEY_K) == GLFW_PRESS)
	{
		//move object demo
		tempVec = ECS::Get<Transform>(2).GetPosition();
		tempVec.z -= 5.f * Timer::dt;
		ECS::Get<Transform>(2).SetPosition(tempVec);
	}

}