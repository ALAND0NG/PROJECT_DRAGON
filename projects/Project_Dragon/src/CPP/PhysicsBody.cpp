#include <Header/PhysicsBody.h>
#include <Header/ECS.h>
#include <Header/Timer.h>

BoundingBox PhysicsBody::GetBox()
{
	return m_BoxCollider;
}

void PhysicsBody::SetBox(glm::vec3 center, float SizeX, float SizeY, float SizeZ)
{
	
	m_BoxCollider.m_Center = center;
	m_BoxCollider.m_MinX = center.x - (0.5 * SizeX);
	m_BoxCollider.m_MaxX = center.x + (0.5 * SizeX);
	m_BoxCollider.m_MinY = center.y - (0.5 * SizeY);
	m_BoxCollider.m_MaxY = center.y + (0.5 * SizeY);
	m_BoxCollider.m_MinZ = center.z - (0.5 * SizeZ);
	m_BoxCollider.m_MaxZ = center.z + (0.5 * SizeZ);
	m_BoxCollider.m_SizeX = SizeX;
	m_BoxCollider.m_SizeY = SizeY;
	m_BoxCollider.m_SizeZ = SizeZ;
	

}

void PhysicsBody::SetMass(float mass)
{
	m_Mass = mass;
}

void PhysicsBody::SetFriction(float friction)
{
	m_Friction = friction;
}

void PhysicsBody::SetVelocity(glm::vec3 velocity)
{
	m_Velocity = velocity;
}

float PhysicsBody::GetMass()
{
	return m_Mass;
}

float PhysicsBody::GetFriction()
{
	return m_Friction;
}

void PhysicsBody::SetGravity(float gravity)
{
	m_Gravity = gravity;
}

glm::vec3 PhysicsBody::GetVelocity()
{
	return m_Velocity;
}

void PhysicsBody::ApplyForce(glm::vec3 force)
{
	
	m_DeltaForce = force;
}

void PhysicsBody::Update(int EntNum)
{
	UpdateBoundingBox(EntNum);

	m_Position = ECS::Get<Transform>(EntNum).GetPosition();
	
	glm::vec3 FrictionForce;

	FrictionForce = m_Velocity;

	glm::normalize(FrictionForce);

	FrictionForce *= (m_Mass * m_Gravity) * m_Friction;

	m_DeltaForce += -FrictionForce;
	
	m_Acceleration = (m_DeltaForce / m_Mass);

	m_Velocity += m_Acceleration;

	m_DeltaForce = glm::vec3(0);

	m_Position += m_Velocity * Timer::dt;
	
	ECS::Get<Transform>(EntNum).SetPosition(m_Position);

}

void PhysicsBody::SetBodyType(int type)
{
	m_BodyType = type;
}

int PhysicsBody::GetBodyType()
{
	return m_BodyType;
}

void PhysicsBody::UpdateBoundingBox(int EntNum)
{
	m_BoxCollider.m_Center = ECS::Get<Transform>(EntNum).GetPosition();
	m_BoxCollider.m_MinX = m_BoxCollider.m_Center.x - (0.5 * m_BoxCollider.m_SizeX);
	m_BoxCollider.m_MaxX = m_BoxCollider.m_Center.x + (0.5 * m_BoxCollider.m_SizeX);
	m_BoxCollider.m_MinY = m_BoxCollider.m_Center.y - (0.5 * m_BoxCollider.m_SizeY);
	m_BoxCollider.m_MaxY = m_BoxCollider.m_Center.y + (0.5 * m_BoxCollider.m_SizeY);
	m_BoxCollider.m_MinZ = m_BoxCollider.m_Center.z - (0.5 * m_BoxCollider.m_SizeZ);
	m_BoxCollider.m_MaxZ = m_BoxCollider.m_Center.z + (0.5 * m_BoxCollider.m_SizeZ);
	
}

