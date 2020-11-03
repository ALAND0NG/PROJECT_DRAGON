#include <ECS.h>

entt::registry* ECS::m_Registry = nullptr;
std::vector<entt::entity> ECS::EntList;


void ECS::AttachRegistry(entt::registry* reg)
{
	m_Registry = reg;
}
