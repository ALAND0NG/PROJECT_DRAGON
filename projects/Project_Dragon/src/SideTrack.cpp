#include "SideTrack.h"

void SideTrack::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).SetVAO(AssetLoader::GetMesh()[1].GetVAO());
	
	//ECS::Get<Material>(startAt).LoadDiffuseFromFile("images/sample.png");
	//ECS::Get<Material>(startAt).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(startAt) = AssetLoader::GetMat()[0];
	//ECS::Add<PhysicsBody>(startAt);
	btVector3 physBodOrigin;
	physBodOrigin.setX(origin.x);
	physBodOrigin.setY(origin.y);
	physBodOrigin.setZ(origin.z);
	//ECS::Get<PhysicsBody>(startAt).AddBody(0, physBodOrigin, btVector3(25, 0, 25));
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;

	ECS::Create(startAt + 1);
	ECS::Add<PhysicsBody>(startAt + 1);
	ECS::Add<Transform>(startAt + 1);
	ECS::Get<PhysicsBody>(startAt + 1).AddBody(0, btVector3(physBodOrigin.getX() + 21, physBodOrigin.getY(), physBodOrigin.getZ()), btVector3(1, 21, 21));
	ECS::Get<PhysicsBody>(startAt + 1).m_Entity = startAt + 1;
	m_EntityIds.push_back(startAt + 1);

	ECS::Create(startAt + 2);
	ECS::Add<PhysicsBody>(startAt + 2);
	ECS::Add<Transform>(startAt + 2);
	ECS::Get<PhysicsBody>(startAt + 2).AddBody(0, btVector3(physBodOrigin.getX() - 21, physBodOrigin.getY(), physBodOrigin.getZ()), btVector3(1, 21, 21));
	ECS::Get<PhysicsBody>(startAt + 2).m_Entity = startAt + 2;
	m_EntityIds.push_back(startAt + 2);

	ECS::Create(startAt + 3);
	ECS::Add<Transform>(startAt + 3);
	ECS::Add<PhysicsBody>(startAt + 3);


	ECS::Get<PhysicsBody>(startAt + 3).AddBody(0, btVector3(physBodOrigin.getX(), physBodOrigin.getY() + 1.3f, physBodOrigin.getZ()), btVector3(21, 0, 21));
	ECS::Get<PhysicsBody>(startAt + 3).m_Entity = startAt + 3;
	m_EntityIds.push_back(startAt + 3);
}