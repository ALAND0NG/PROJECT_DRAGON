#include <Enemy.h>

void Enemy::Update()
{
	mTimer += Timer::dt;

	if (mTimer >= 2)
	{ //Update general enemy information every 2 seconds to reduce computing
		thisPosition = ECS::Get<PhysicsBody>(entityNumber).GetBody()->getCenterOfMassTransform().getOrigin();
		playerPosition = ECS::Get<PhysicsBody>(0).GetBody()->getCenterOfMassTransform().getOrigin();
		distance.setX(powf(thisPosition.getX() - playerPosition.getX(), 2.0f));
		distance.setY(powf(thisPosition.getY() - playerPosition.getY(), 2.0f));
		distance.setZ(powf(thisPosition.getZ() - playerPosition.getZ(), 2.0f));

		std::cout << "\nX: " << distance.getX() << "\nY: " << distance.getY() << "\nZ: " << distance.getZ() << "\n\n";
		distanceNorm = sqrtf(distance.getX() + distance.getY() + distance.getZ());

		//Chance behavior of enemy based on distance

		//Very Close

		//

		//Close

		//Mid Range

		//Long Range
	}
}