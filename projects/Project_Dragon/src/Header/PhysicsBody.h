#pragma once
//This is the class for ECS
//using basically only AABB
//Add this to the entitites you want to have physics
#include <GLM/glm.hpp>
#include <vector>

struct BoundingBox //This defines the bounding box, any single physics body can have multiple of these
{
	glm::vec3 m_Center;
	float m_MinX;
	float m_MaxX;
	float m_MinY;
	float m_MaxY;
	float m_MaxZ;
	float m_MinZ;
	float m_SizeX;
	float m_SizeY;
	float m_SizeZ;
};

class PhysicsBody
{
public:
	
	BoundingBox GetBox();

	void SetBox(glm::vec3 center, float SizeX, float SizeY, float SizeZ);

	void SetMass(float mass);

	void SetFriction(float friction);

	void SetVelocity(glm::vec3 velocity);

	float GetMass();

	float GetFriction();

	void SetPosition(glm::vec3 position);

	glm::vec3 GetPosition();

	void SetGravity(float gravity);

	glm::vec3 GetVelocity();

	void ApplyForce(glm::vec3 force);

	void Update(int EntNum);

	void SetBodyType(int type);//0 for static, 1 for dynamic, 2 for kinematic, 3 for bullet

	int GetBodyType();//0 for static, 1 for dynamic, 2 for kinematic, 3 for bullet

	glm::vec3 GetDeltaForce();

	void SetGravityScale(int gravityscale);

	float GetGraviy();

	

private:
	
	BoundingBox m_BoxCollider;
	glm::vec3 m_Position;
	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	glm::vec3 m_DeltaForce;
	glm::vec3 m_AppliedForce;
	float m_Mass;
	float m_Friction;//Coeficient of friction
	float m_Gravity = -9.8f;//set in here so different things can be made to fall at different velocities
	float m_GravityScale = 1.f;

	int m_BodyType;

	void UpdateBoundingBox(int EntNum);
	void CalculateDeltaForce();
};
