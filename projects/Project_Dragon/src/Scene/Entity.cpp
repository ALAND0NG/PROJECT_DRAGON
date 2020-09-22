#include "Entity.h"

Entity::Entity(entt::entity handle)
{
	m_EntityHandle = handle;
}

entt::entity Entity::GetHandle()
{
	return m_EntityHandle;
}


