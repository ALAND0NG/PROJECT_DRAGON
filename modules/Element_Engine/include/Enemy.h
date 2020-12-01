#pragma once
#include <ECS.h>
#include <Timer.h>
#include <ECS.h>
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
	int entityNumber = 2;
	float distanceNorm = 100.0f;
	float mTimer = 0.0f;

	//External Values
	btVector3 playerPosition;

	void Update();
};