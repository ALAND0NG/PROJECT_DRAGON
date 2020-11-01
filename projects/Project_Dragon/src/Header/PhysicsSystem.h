#pragma once
#include <Header/PhysicsBody.h>
#include <Header/ECS.h>
static class PhysicsSystem
{
public:
	static void Update();
	static bool AABB(PhysicsBody body1, PhysicsBody body2); //Axis Aligned Bounding Boxes Test, returns if there is a collision
private:
	
	static std::vector<int> m_PhysicsBody_IDs;
};