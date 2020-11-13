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
	m_EntityIds.push_back(startAt);
	std::cout << "Loaded a prefab, starting at: " << startAt << std::endl;
}