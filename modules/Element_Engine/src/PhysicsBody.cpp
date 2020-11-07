#include <PhysicsBody.h>
#include <ECS.h>
#include <Timer.h>
#include <PhysicsSystem.h>

btRigidBody* PhysicsBody::GetBody()
{
	return m_Body;
}

void PhysicsBody::SetBody(btRigidBody* body)
{
	m_Body = body;
}

void PhysicsBody::AddBody(float mass, btVector3 origin, btVector3 size)
{
	btCollisionShape* colShape = new btBoxShape(size);

	btTransform startTransform;
	startTransform.setIdentity();

	bool isDynamic = true;
	if (mass == 0.f)
		isDynamic = false;

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	startTransform.setOrigin(origin);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	
	PhysicsSystem::m_World->addRigidBody(body);
	PhysicsSystem::m_bodies.push_back(body);
	m_BodyId = PhysicsSystem::m_bodies.size() - 1;
	

}
