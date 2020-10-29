#pragma once
#include <Header/PhysicsBody.h>
#include <Header/ECS.h>
static class PhysicsSystem
{
public:
	static void Update();
private:
	static bool AABB(PhysicsBody body1, int boxid1, PhysicsBody body2, int boxid2); //Axis Aligned Bounding Boxes Test, returns if there is a collision
};