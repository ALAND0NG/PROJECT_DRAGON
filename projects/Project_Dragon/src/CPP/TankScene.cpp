#include <Header/TankScene.h>

void TankScene::InitScene()
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
	ECS::Get<LightSource>(2).m_Colour = glm::vec3(1.0f, 1.f, 1.f);


	ECS::Create(3);
	ECS::Add<Mesh>(3);
	ECS::Add<Transform>(3);
	ECS::Add<Material>(3);
	ECS::Get<Transform>(3).SetPosition(glm::vec3(5.f, -12.f, 0.f));
	ECS::Get<Transform>(3).SetScale(glm::vec3(5.f, 5.f, 5.f));
	ECS::Get<Mesh>(3).LoadOBJ("models/temple.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Get<Material>(3).LoadDiffuseFromFile("images/stone_001_diffuse.png");
	ECS::Get<Material>(3).LoadDiffuse2FromFile("images/trappin.jpg");
	ECS::Get<Material>(3).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(3).Tex1Str = 1.f;
	ECS::Get<Material>(3).Tex2Str = 0.f;
	ECS::Get<Material>(3).SetAll(0.1f);

	ECS::Create(4);
	ECS::Add<LightSource>(4);
	ECS::Add<Mesh>(4);
	ECS::Add<Transform>(4);
	ECS::Get<LightSource>(4).m_Colour = glm::vec3(1.f, 1.f, 1.f);
	ECS::Get<Transform>(4).SetPosition(glm::vec3(5.f, -9.f, 5.f));

	ECS::Create(5);
	ECS::Add<LightSource>(5);
	ECS::Add<Mesh>(5);
	ECS::Add<Transform>(5);
	ECS::Get<LightSource>(5).m_Colour = glm::vec3(1.f, 1.f, 1.f);
	ECS::Get<Transform>(5).SetPosition(glm::vec3(5.f, -9.f, 5.f));
}

void TankScene::Update()
{
}
