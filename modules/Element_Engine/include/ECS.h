#pragma once
#include <vector>
#include <iostream>
#include "entt.hpp"

//all the component includes
#include <Camera.h>
#include <Mesh.h>
#include <Transform.h>
#include <Material.h>
#include <LightSource.h>
#include <PhysicsBody.h>
#include <Parent.h>
#include <Skybox.h>
#include <MorphAnimator.h>
#include <AnimationBlender.h>
#include <Player.h>
#include <Enemy.h>
#include <UI.h>

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

	static int GetSize()
	{
		return EntList.size();
	}

	static void DestroyAllEntities()
	{
		for (int i = 0; i < EntList.size(); i++)
		{
			m_Registry->destroy(EntList[i]);
			
		}
		EntList.clear();
	}
	

private:
	static entt::registry* m_Registry;
	static std::vector<entt::entity> EntList;
};