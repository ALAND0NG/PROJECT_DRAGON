#include <Header/PhysicsBody.h>
#include <Header/ECS.h>
#include <Header/Timer.h>
int PhysicsBody::GetBoxCount()
{
	return m_BoundindBoxes.size();
}

BoundingBox PhysicsBody::GetBox(int box_number)
{
	return m_BoundindBoxes[box_number];
}

void PhysicsBody::AddBox(glm::vec3 center, float SizeX, float SizeY, float SizeZ)
{
	BoundingBox tempBox;
	tempBox.m_Center = center;
	tempBox.m_MinX = center.x - (0.5 * SizeX);
	tempBox.m_MaxX = center.x + (0.5 * SizeX);
	tempBox.m_MinY = center.y - (0.5 * SizeY);
	tempBox.m_MaxY = center.y + (0.5 * SizeY);
	tempBox.m_MinZ = center.z - (0.5 * SizeZ);
	tempBox.m_MaxZ = center.z + (0.5 * SizeZ);

}

void PhysicsBody::SetMass(float mass)
{
	m_Mass = mass;
}

void PhysicsBody::SetFriction(float friction)
{
	m_Friction = friction;
}

float PhysicsBody::GetMass()
{
	return m_Mass;
}

float PhysicsBody::GetFriction()
{
	return m_Friction;
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
	m_Position = ECS::Get<Transform>(EntNum).GetPosition();
	
	m_Acceleration = (m_DeltaForce / m_Mass);
	
	std::cout << m_Acceleration.x;

	m_Velocity += m_Acceleration;

	m_Position += m_Velocity * Timer::dt;
	
	ECS::Get<Transform>(EntNum).SetPosition(m_Position);

}
