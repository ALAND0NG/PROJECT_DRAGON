#pragma once
#include <vector>
//This is the base class for prefabs
//A prefab is basically going to act as a big group of entites that get generated through as a predefined init script
//and keep track of the entity id's attached to all of them in a std::vector
class Prefab
{
public:
	virtual void LoadPrefab(int startAt);//The instanciating system will look at the next available entity id, and pass that on to this function
	virtual std::vector<int> GetEntityIds();//returns the vector containing all the entity IDS
private:
	std::vector<int> m_EntityIds;//The container to keep track of all the entities

};