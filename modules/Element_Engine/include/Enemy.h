#pragma once
#include <ECS.h>
#include <ElementEngine.h>
#include <AssetLoader.h>
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
	float distanceNorm = 100.0f;
	float mTimer = 0.0f;

	//External Values
	btVector3 playerPosition;

	void Update() {
		mTimer += Timer::dt;

		if (mTimer >= 2) { //Update general enemy information every 2 seconds to reduce computing
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
};