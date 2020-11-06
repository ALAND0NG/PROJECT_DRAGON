/*
#include <TankData.h>
#include <ECS.h>
#include <Timer.h>

void TankData::AttachBullet(int BulletID)
{
	m_BulletID = BulletID;
}

void TankData::AttachTank(int TankID)
{
	m_TankID = TankID;
}

void TankData::Shoot()
{
	

	ECS::Get<PhysicsBody>(m_BulletID).SetVelocity(m_Forward * m_BulletSpeed * Timer::dt);
	
}

void TankData::Rotate(float angle)
{
	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, glm::radians(angle), glm::vec3(0,1,0));
	m_Forward = glm::vec3(rotationMat * glm::vec4(m_Forward, 1.0));
	ECS::Get<Transform>(m_TankID).SetRotation(glm::vec3(0,1,0), glm::radians(angle));
	//glm::rotate(m_Forward, glm::radians(10.f), glm::vec3(1.f, 0.f,0.f));

	
}

void TankData::SetBulletSpeed(float BulletSpeed)
{
	m_BulletSpeed = BulletSpeed;
}

glm::vec3 TankData::GetForward()
{
	return m_Forward;
}

void TankData::ResetForward()
{
	m_Forward = glm::vec3(1.f, 0.f, 0.f);
}
*/