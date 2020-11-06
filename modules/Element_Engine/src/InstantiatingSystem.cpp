#include <InstantiatingSystem.h>


std::vector<Prefab*> InstantiatingSystem::m_Prefabs;

void InstantiatingSystem::InitPrefab(int index, glm::vec3 origin)
{
	std::cout << "Loading Prefab\n";
	m_Prefabs[index]->LoadPrefab(ECS::GetSize(), origin);
}

void InstantiatingSystem::AddPrefab(Prefab* prefab)
{
	m_Prefabs.push_back(prefab);
}
