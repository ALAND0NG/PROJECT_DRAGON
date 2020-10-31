#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm.hpp>
#include <GLM/gtx/rotate_vector.hpp>

class TankData
{
public:
	void AttachBullet(int BulletID);//Sets the ID for the bullet since I will load them at the begining and simply teleport them rather than instance
	
	void AttachTank(int TankID);

	void Shoot();

	void Rotate(float angle);//True will rotate clockwise, and vice versa

	void SetBulletSpeed(float BulletSpeed);

	glm::vec3 GetForward();

private:
	int m_BulletID;
	int m_TankID;
	glm::vec3 m_Forward = glm::vec3(1.f, 0.f, 0.f);//used to know what direction to shoot as well as move forward
	float m_BulletSpeed;
	bool m_BulletShot;//true if a bullet has been fired

};