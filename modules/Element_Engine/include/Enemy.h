#pragma once
#include <Timer.h>
//basically playerdata but for the enemy
class Enemy
{
public:
	//Enemy Stat Values
	int m_hp = 5;

	//Enemy Behavior Values
	float Aggression = 0.5f;
	float Confidence = 0.5f;

	//Internal Values
	btVector3 thisPosition;
	btVector3 distance;
	int entityNumber = 0;
	float mTimer = 0.0f;

	//External Values
	btVector3 playerPosition;

	void Update() {
		mTimer += Timer::dt;

		if (mTimer >= 2) { //Update general enemy information every 2 seconds to reduce computing
			thisPosition = ECS::Get<PhysicsBody>(entityNumber).GetBody()->getCenterOfMassTransform().getOrigin();
			playerPosition = ECS::Get<PhysicsBody>(0).GetBody()->getCenterOfMassTransform().getOrigin();
			distance.setX(sqrtf(powf(thisPosition.getX() - playerPosition.getX(), 2.0f)));
			distance.setY(sqrtf(powf(thisPosition.getY() - playerPosition.getY(), 2.0f)));
			distance.setZ(sqrtf(powf(thisPosition.getZ() - playerPosition.getZ(), 2.0f)));

			std::cout << "\nX: " << distance.getX() << "\nY: " << distance.getY() << "\nZ: " << distance.getZ() << "\n\n";
		}
	}
};