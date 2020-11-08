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
	m_Body= new btRigidBody(rbInfo);

	
	PhysicsSystem::m_World->addRigidBody(m_Body);
	PhysicsSystem::m_bodies.push_back(m_Body);
	m_BodyId = PhysicsSystem::m_bodies.size() - 1;
	m_Body->setFriction(0.01);
	

}

void PhysicsBody::SetLinearVelocity(btVector3 direction)
{
	m_Body->setLinearVelocity(direction);
}
