#pragma once
#include <vector>
#include <iostream>
#include "entt.hpp"

#include <Header/Camera.h>

#include <Header/Mesh.h>
#include <Header/Transform.h>

class ECS
{
public:

	static void AttachRegistry(entt::registry* reg);

	static void Create(unsigned int EntId)
	{
		entt::entity id = m_Registry->create();
		EntList.push_back(id);
		EntList[EntId] = id;
	}

	template<typename T, typename... Args>
	static void Add(Args&&... args, unsigned int EntityNum)
	{
		m_Registry->emplace<T>(EntList[EntityNum], std::forward<Args>(args)...);
	}

	template<typename T>
	static T& Get(unsigned int EntityNum)
	{
		return m_Registry->get<T>(EntList[EntityNum]);
	}

	static entt::registry* GetReg()
	{
		return m_Registry;
	}
	template<typename T>
	static bool Has(unsigned int EntityNum)
	{
		if (m_Registry->has<T>(EntList[EntityNum]))
			return true;
		else
			return false;
	}

private:
	static entt::registry* m_Registry;
	static std::vector<entt::entity> EntList;
};