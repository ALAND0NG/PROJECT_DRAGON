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

	ECS::Get<PhysicsBody>(startAt).AddBody(0, physBodOrigin, btVector3(100, 0, 100));
	ECS::Get<PhysicsBody>(startAt).m_Entity = startAt;
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;

}