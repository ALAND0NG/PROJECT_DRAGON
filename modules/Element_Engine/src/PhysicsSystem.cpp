#include <PhysicsSystem.h>
#include <Timer.h>
#include <GLM/gtc/type_ptr.hpp>
#include <BackEnd.h> //I hope this doesn't break it :)
btDiscreteDynamicsWorld* PhysicsSystem::m_World;

std::vector<btRigidBody*> PhysicsSystem::m_bodies;


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

	m_World->setGravity(btVector3(0, -5, 0));

	/*
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
		bodies.push_back(body);
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

		startTransform.setOrigin(btVector3(2, 50, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		m_World->addRigidBody(body);
		bodies.push_back(body);

		btTransform trans = body->getWorldTransform();
		//ECS::Get<Transform>(1).SetPosition(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));
	}
	*/
}

void PhysicsSystem::Update()
{
	
	
	
	auto reg = ECS::GetReg();

	//auto view = reg->view<PhysicsBody, Transform>();
	/*
	m_World->stepSimulation(0);
	for (int i = 0; i < reg->size(); i++)
	{
		if (ECS::Has<PhysicsBody>(i))
		{

	
		btTransform trans = m_bodies[ECS::Get<PhysicsBody>(0).m_BodyId]->getWorldTransform();
		
		ECS::Get<Transform>(0).SetPosition(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));
	
	

	//	ECS::Get<Transform>(ECS::Get<PhysicsBody>(i).m_Entity).SetPosition(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));
	//	std::cout << trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " << trans.getOrigin().getZ() << "\n";
		}


		//}
	}
	
	ECS::Get<PhysicsBody>(0).SetLinearVelocity(btVector3(1, 1, 1));
	*/
	m_World->stepSimulation(Timer::dt, 10);
	for (int i = 0; i < reg->size(); i++)
	{
		if (ECS::Has<PhysicsBody>(i))
		{
			btTransform trans = m_bodies[ECS::Get<PhysicsBody>(i).m_BodyId]->getWorldTransform();

			ECS::Get<Transform>(i).SetPosition(glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ())));

		}
	}

}

btDiscreteDynamicsWorld* PhysicsSystem::GetWorld()
{
	return m_World;
}

std::vector<btRigidBody*> PhysicsSystem::GetBodies()
{
	return m_bodies;
}
