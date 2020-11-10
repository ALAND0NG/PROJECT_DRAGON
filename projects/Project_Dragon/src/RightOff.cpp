#include "RightOff.h"

void RightOff::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).LoadOBJ("models/RightOff.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(startAt).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(startAt).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(startAt).SetAll(1.f);
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;
}