#include "TestPrefab.h"

void TestPrefab::LoadPrefab(int startAt)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(-2, 2, 0));
	ECS::Get<Mesh>(startAt).LoadOBJ("models/cube.obj", glm::vec4(1,1,1,1));
	ECS::Get<Material>(startAt).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(startAt).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(startAt).SetAll(1.f);
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;
	
}
