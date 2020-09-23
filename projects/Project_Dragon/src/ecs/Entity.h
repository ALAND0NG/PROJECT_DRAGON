#pragma once

#include "Scene/Scene.h"

#include "entt.hpp"

class Entity
{
public:
	Entity() = default;
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		return m_Scene->m_SceneReg->emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		return m_Scene->m_SceneReg.get<T>(m_EntityHandle);
	}

	operator uint32_t() const { return (uint32_t)m_EntityHandle; }

private:
	entt::entity m_EntityHandle{ entt::null };
	Scene* m_Scene = nullptr;
};