#include <Player.h>

bool Player::Shoot(float range)
{
	btVector3 playerPosition = ECS::Get<PhysicsBody>(m_PlayerData.m_EntityId).GetBody()->getCenterOfMassTransform().getOrigin();
	glm::vec3 lookDir = ECS::Get<Camera>(m_PlayerData.m_EntityId).GetForward();
	lookDir *= range;
	btVector3 to = BtToGlm::GLMTOBTV3(lookDir);
	to += playerPosition;
	btCollisionWorld::ClosestRayResultCallback Results(playerPosition, to);

	PhysicsSystem::GetWorld()->rayTest(playerPosition, to, Results);

	std::cout << "Raycast ended at point: " << to.getX() << ", " << to.getY() << ", " << to.getZ() << std::endl;

	return Results.hasHit();
}

void Player::Update()
{
}

void Player::CheckJump()
{

	btVector3 playerPosition = ECS::Get<PhysicsBody>(m_PlayerData.m_EntityId).GetBody()->getCenterOfMassTransform().getOrigin();
	btVector3 to = playerPosition;
	to.setY(to.getY() - 2.f);
	//to += playerPosition;
	btCollisionWorld::ClosestRayResultCallback Results(playerPosition, to);

	PhysicsSystem::GetWorld()->rayTest(playerPosition, to, Results);

	if (Results.hasHit())
	{
		m_PlayerData.m_CanJump = true;
	}
	else
	{
		m_PlayerData.m_CanJump = false;
	}
}

PlayerData Player::GetPlayerData()
{
	return m_PlayerData;
}

void Player::SetPlayerData(PlayerData playdata)
{
	m_PlayerData = playdata;
}
