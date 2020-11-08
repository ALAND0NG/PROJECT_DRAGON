#include "StraightTrack.h"

void StraightTrack::LoadPrefab(int startAt, glm::vec3 origin)
{
	ECS::Create(startAt);
	ECS::Add<Mesh>(startAt);
	ECS::Add<Material>(startAt);
	ECS::Add<Transform>(startAt);
	ECS::Add<PhysicsBody>(startAt);
	ECS::Get<Transform>(startAt).SetPosition(glm::vec3(origin));
	ECS::Get<Mesh>(startAt).LoadOBJ("models/StraightTrack.obj", glm::vec4(1, 1, 1, 1));
	ECS::Get<Material>(startAt).LoadDiffuseFromFile("images/sample.png");
	ECS::Get<Material>(startAt).LoadSpecularFromFile("images/sample_spec.png");
	ECS::Get<Material>(startAt).SetAll(1.f);
	btVector3 physBodOrigin;
	physBodOrigin.setX(origin.x);
	physBodOrigin.setY(origin.y);
	physBodOrigin.setZ(origin.z);

	ECS::Get<PhysicsBody>(startAt).AddBody(0, physBodOrigin, btVector3(100, 1, 100));
	ECS::Get<PhysicsBody>(startAt).m_Entity = startAt;
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;

}