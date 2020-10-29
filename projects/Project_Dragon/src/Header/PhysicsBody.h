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
};

class PhysicsBody
{
public:
	
	int GetBoxCount();

	BoundingBox GetBox(int box_number);

	void AddBox(glm::vec3 center, float SizeX, float SizeY, float SizeZ);

	void SetMass(float mass);

	void SetFriction(float friction);

	float GetMass();

	float GetFriction();

	glm::vec3 GetVelocity();

	void ApplyForce(glm::vec3 force);

	void Update(int EntNum);

private:
	std::vector<BoundingBox> m_BoundindBoxes; //since we let a single physics body have multiple boxes, we need a way to store them
	glm::vec3 m_Position;
	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	glm::vec3 m_DeltaForce;
	float m_Mass;
	float m_Friction;


};
