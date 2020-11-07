#include <PhysicsSystem.h>
#include <Timer.h>
#include <GLM/gtc/type_ptr.hpp>
btDiscreteDynamicsWorld* PhysicsSystem::m_World;


std::vector<btCollisionShape*> colShapes;
void PhysicsSystem::Init()
{
	//I STOLE THIS FROM BULLET GITHUB PAGE GOD THIS IS SO TEMPORARY

	///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	m_World = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	m_World->setGravity(btVector3(0, -1, 0));

	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(5.), btScalar(5.), btScalar(5.)));

		colShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -5, 0));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		m_World->addRigidBody(body);
	}

	{
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		colShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 100, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		m_World->addRigidBody(body);
	}


}

void PhysicsSystem::Update()
{
	
	{
		m_World->stepSimulation(1.f / 60.f, 10);
		//print positions of all objects
		for (int j = m_World->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = m_World->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			//glm::vec3 glVec3(ECS::Get<Transform>(1).GetPosition());

			//trans.setOrigin(btVector3(glVec3.x, glVec3.y, glVec3.z));
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			glm::vec3 fuck;
			fuck.x = trans.getOrigin().getX();
			fuck.y = trans.getOrigin().getY();
			fuck.z = trans.getOrigin().getZ();

			ECS::Get<Transform>(1).SetPosition(fuck);
			//ECS::Get<Transform>(1).SetPosition(ECS::Get<Transform>(1).GetPosition() += glm::vec3(0.1f, 0.1f, 0.1f) * Timer::dt);
			//ECS::Get<Transform>(1).ComputeGlobalMat();
			//std::cout << trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " << trans.getOrigin().getZ() << std::endl;
			std::cout << ECS::Get<Transform>(1).GetPosition().x << " " << ECS::Get<Transform>(1).GetPosition().y << " " << ECS::Get<Transform>(1).GetPosition().z << std::endl;

		}


	}

}
