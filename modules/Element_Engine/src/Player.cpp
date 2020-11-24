#include <Player.h>

bool Player::Shoot()
{
	btVector3 playerPosition = ECS::Get<PhysicsBody>(m_PlayerData.m_EntityId).GetBody()->getCenterOfMassTransform().getOrigin();
	glm::vec3 lookDir = ECS::Get<Camera>(m_PlayerData.m_EntityId).GetForward();
	lookDir *= 5;
	btVector3 to = BtToGlm::GLMTOBTV3(lookDir);

	btCollisionWorld::ClosestRayResultCallback Results(playerPosition, to);

	PhysicsSystem::GetWorld()->rayTest(playerPosition, to, Results);

	
	return Results.hasHit();
}

PlayerData Player::GetPlayerData()
{
	return m_PlayerData;
}

void Player::SetPlayerData(PlayerData playdata)
{
	m_PlayerData = playdata;
}
