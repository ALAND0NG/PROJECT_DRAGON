#pragma once
#include <Prefab.h>

//temporary test prefab
class TestPrefab : public Prefab

{
public:
	void LoadPrefab(int startAt, glm::vec3 origin) override;
private:
	std::vector<int> m_EntityIds;//The container to keep track of all the entities
};