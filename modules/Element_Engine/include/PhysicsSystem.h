#pragma once
#include <PhysicsBody.h>
#include <ECS.h>
#include <bullet/btBulletDynamicsCommon.h>
static class PhysicsSystem
{
public:
	static void Init();
	static void Update();

private:
	static btDiscreteDynamicsWorld* m_World;
	
};