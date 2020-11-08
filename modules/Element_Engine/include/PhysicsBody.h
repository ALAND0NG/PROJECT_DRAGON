#pragma once
//This is the class for ECS
//using basically only AABB
//Add this to the entitites you want to have physics
#include <GLM/glm.hpp>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>

class PhysicsBody
{
public:

	btRigidBody* GetBody();
	void SetBody(btRigidBody* body);
	//for now all bodies will be boxes, will change later but really I just want to get

	void SetLinearVelocity(btVector3 direction);
	//something up and running
	void AddBody(float mass, btVector3 origin, btVector3 size);

	int m_BodyId;//this for da world thing

private:

	btRigidBody* m_Body = nullptr;
	

};
