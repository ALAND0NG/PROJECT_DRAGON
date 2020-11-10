#pragma once
#include <Prefab.h>
static class InstantiatingSystem
{
public:
	static void InitPrefab(int index, glm::vec3 origin);
	static void AddPrefab(Prefab* prefab);
private:
	static std::vector<Prefab*> m_Prefabs;//A list of all prefabs, all these prefabs also contain a vector of all entity numbers they contain
	static std::vector<Mesh> m_Meshes;
};