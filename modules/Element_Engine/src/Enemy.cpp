#include <Enemy.h>

void Enemy::Update()
{
	mTimer += Timer::dt;

	if (mTimer >= 0.5f)
	{ //Update general enemy information every 2 seconds to reduce computing
		mTimer = 0.0f;
		movementDirection.x = 0;
		movementDirection.z = 0;

		thisPosition = ECS::Get<PhysicsBody>(entityNumber).GetBody()->getCenterOfMassTransform().getOrigin();
		playerPosition = ECS::Get<PhysicsBody>(0).GetBody()->getCenterOfMassTransform().getOrigin();
		distance.setX(powf(thisPosition.getX() - playerPosition.getX(), 2.0f));
		distance.setY(powf(thisPosition.getY() - playerPosition.getY(), 2.0f));
		distance.setZ(powf(thisPosition.getZ() - playerPosition.getZ(), 2.0f));

		//Chance behavior of enemy based on distance

		//Red Zone
		if (distanceNorm < lookRange * 2) {
			std::cout << "\nRetreating\n";
			if (thisPosition.getX() < playerPosition.getX()) {
				movementDirection.x = -1;
			}
			else movementDirection.x = 1;
			if (thisPosition.getZ() < playerPosition.getZ()) {
				movementDirection.z = -1;
			}
			else movementDirection.z = 1;
		}

		//Orange Zone
		else if (distanceNorm < lookRange * 3) {
			std::cout << "\Attacking\n";
		}

		//Yellow Zone
		else if (distanceNorm < lookRange * 5) {
			std::cout << "\Hunting\n";
			if (thisPosition.getX() < playerPosition.getX()) {
				movementDirection.x = 1;
			}
			else movementDirection.x = -1;
			if (thisPosition.getZ() < playerPosition.getZ()) {
				movementDirection.z = 1;
			}
			else movementDirection.z = -1;
		}
		std::cout << "\nX: " << distance.getX() << "\nY: " << distance.getY() << "\nZ: " << distance.getZ() << "\n\n";
		distanceNorm = sqrtf(distance.getX() + distance.getY() + distance.getZ());
		std::cout << "\nDistance: " << distanceNorm << "\n\n\n\n";
	}
	ECS::Get<PhysicsBody>(entityNumber).SetLinearVelocity(btVector3(movementDirection.x * 2, 0, movementDirection.z * 2));
}