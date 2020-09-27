#pragma once
#include <vector>
#include <iostream>
#include "entt.hpp"

//only make one of these objects
class ECS
{
public:
	
	void AttachRegistry(entt::registry* reg)
	{
		m_Registry = reg;
	}
	
	void Create(unsigned int EntId)
	{
		entt::entity id = m_Registry->create();
		EntList.push_back(id);
		EntList[EntId] = id;
	}

	template<typename T, typename... Args>
	void Add(Args&&... args, unsigned int EntityNum)
	{
		m_Registry->emplace<T>(EntList[EntityNum], std::forward<Args>(args)...);
	}

	template<typename T>
	T& Get(unsigned int EntityNum)
	{
		return m_Registry->get<T>(EntList[EntityNum]);
	}


private:
	entt::registry* m_Registry;
	std::vector<entt::entity> EntList; //list of all the entities
};

class TestComponent
{
public:
	int lol = 1;
};