#include "TestPrefab.h"
#include <AssetLoader.h>
void TestPrefab::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Add<PhysicsBody>(startAt);
	ECS::Add<LightSource>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).LoadOBJ("models/Cube.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(startAt) = AssetLoader::GetMat()[0];
	ECS::Get<Material>(startAt).SetAll(1.f);
	btVector3 physBodOrigin;
	physBodOrigin.setX(origin.x);
	physBodOrigin.setY(origin.y);
	physBodOrigin.setZ(origin.z);
	
	ECS::Get<PhysicsBody>(startAt).AddBody(0.000001,physBodOrigin, btVector3(2,2,2), 0.f);
	ECS::Get<PhysicsBody>(startAt).m_Entity = startAt;

	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;
}