#include "StraightTrack.h"

void StraightTrack::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Add<PhysicsBody>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).SetVAO(AssetLoader::GetMesh()[0].GetVAO());
	ECS::Get<Material>(startAt) = AssetLoader::GetMat()[0];
	btVector3 physBodOrigin;
	physBodOrigin.setX(origin.x);
	physBodOrigin.setY(origin.y);
	physBodOrigin.setZ(origin.z);

	ECS::Get<PhysicsBody>(startAt).AddBody(0, physBodOrigin, btVector3(25, 0, 25));
	ECS::Get<PhysicsBody>(startAt).m_Entity = startAt;
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;

	ECS::Create(startAt + 1);
	ECS::Add<PhysicsBody>(startAt + 1);
	ECS::Add<Transform>(startAt + 1);
	ECS::Get<PhysicsBody>(startAt + 1).AddBody(0, btVector3(physBodOrigin.getX(), physBodOrigin.getY(), physBodOrigin.getZ() + 21), btVector3(25, 25, 1));
	ECS::Get<PhysicsBody>(startAt + 1).m_Entity = startAt + 1;
	m_EntityIds.push_back(startAt + 1);

	ECS::Create(startAt + 2);
	ECS::Add<PhysicsBody>(startAt + 2);
	ECS::Add<Transform>(startAt + 2);
	ECS::Get<PhysicsBody>(startAt + 2).AddBody(0, btVector3(physBodOrigin.getX(), physBodOrigin.getY(), physBodOrigin.getZ() - 21), btVector3(25, 25, 1));
	ECS::Get<PhysicsBody>(startAt + 2).m_Entity = startAt + 2;
	m_EntityIds.push_back(startAt + 2);

	ECS::Create(startAt + 3);
	ECS::Add<PhysicsBody>(startAt + 3);
	ECS::Add<Transform>(startAt + 3);
	ECS::Add<Mesh>(startAt + 3);
	ECS::Add<Material>(startAt + 3);

	ECS::Get<Mesh>(startAt + 3).LoadOBJ("Models/pillar.obj", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ECS::Get<Transform>(startAt + 3).SetPosition(glm::vec3(0.f, 0.f, 0.f));
	ECS::Get<Transform>(startAt + 3).SetScale(glm::vec3(5.f, 5.f, 5.f));
	ECS::Add<Material>(startAt + 3);
	ECS::Get<Material>(startAt + 3).LoadDiffuseFromFile("images/red.jpg");
	ECS::Get<Material>(startAt + 3).LoadSpecularFromFile("images/red.jpg");
	ECS::Get<Material>(startAt + 3).SetAll(1.f);
	//ECS::Get<PhysicsBody>(startAt + 3).AddBody(1000000000, btVector3(0, 5, 0), btVector3(2, 2, 2));
	//ECS::Get<PhysicsBody>(startAt + 3).m_Entity = startAt + 3;
	m_EntityIds.push_back(startAt + 3);
}