#pragma once
#include <Prefab.h>

class StraightTrack : public Prefab {
public:
	void LoadPrefab(int startAt, glm::vec3 origin) override;
private:
	std::vector<int> m_EntityIds;//The container to keep track of all the entities
};