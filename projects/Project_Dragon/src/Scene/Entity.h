#pragma once

#include "Scene.h"

#include "entt.hpp"

class Entity
{
public:
	Entity();
	Entity(entt::entity handle);
	Entity(const Entity& other) = default;
	entt::entity GetHandle();
	

private:
	entt::entity m_EntityHandle;
	
};