#include "TestPrefab.h"

void TestPrefab::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Add<PhysicsBody>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).LoadOBJ("models/Demo_Room.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(startAt).LoadDiffuseFromFile("images/Stone_001_Diffuse.png");
	ECS::Get<Material>(startAt).LoadSpecularFromFile("images/Stone_001_Specular.png");
	ECS::Get<Material>(startAt).SetAll(1.f);
	btVector3 physBodOrigin;
	physBodOrigin.setX(origin.x);
	physBodOrigin.setY(origin.y);
	physBodOrigin.setZ(origin.z);
	
	ECS::Get<PhysicsBody>(startAt).AddBody(0,physBodOrigin, btVector3(2,2,2));
	ECS::Get<PhysicsBody>(startAt).m_Entity = startAt;
	
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;
}