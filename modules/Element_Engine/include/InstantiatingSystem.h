#pragma once
#include <Prefab.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

static class InstantiatingSystem
{
public:
	//for the prefabs that aren't loaded from a file
	//leaving this here to not break anything
	static void InitPrefab(int index, glm::vec3 origin);
	static void AddPrefab(Prefab* prefab);
	//static std::vector<StartEnd*> GetInstantiated();

	//to load a prefab from a file
	static void LoadPrefabFromFile(int index, glm::vec3 origin, std::string filename);

private:
	static std::vector<Prefab*> m_Prefabs;//A list of all prefabs, all these prefabs also contain a vector of all entity numbers they contain
	static std::vector<Mesh> m_Meshes;
	//static std::vector<StartEnd*> m_Instantiated;//contains a list of the prefabs that have already been made.
};