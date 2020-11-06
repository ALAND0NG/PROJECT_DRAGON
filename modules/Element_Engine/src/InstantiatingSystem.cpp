#include <InstantiatingSystem.h>


std::vector<Prefab*> InstantiatingSystem::m_Prefabs;

void InstantiatingSystem::InitPrefab(int index)
{
	std::cout << "Loading Prefab\n";
	m_Prefabs[index]->LoadPrefab(ECS::GetSize());
}

void InstantiatingSystem::AddPrefab(Prefab* prefab)
{
	m_Prefabs.push_back(prefab);
}
