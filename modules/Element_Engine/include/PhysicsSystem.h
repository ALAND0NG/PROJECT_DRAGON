#pragma once
#include <PhysicsBody.h>
#include <ECS.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <DebugDrawing.h>

static class PhysicsSystem
{
public:
	static void Init();
	static void Update();

	static btDiscreteDynamicsWorld* GetWorld();

	static std::vector<btRigidBody*> GetBodies();

	static btDiscreteDynamicsWorld* m_World;
	static std::vector<btRigidBody*> m_bodies;
	static BulletDebugDrawer_OpenGL drawer;

};