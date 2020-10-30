#include <Header/PhysicsSystem.h>
#include <Header/Timer.h>

std::vector<int> PhysicsSystem::m_PhysicsBody_IDs;



void PhysicsSystem::Update()
{
	auto reg = ECS::GetReg();

	for (int i = 0; i < reg->size(); i++)
	{
		if (ECS::Has<PhysicsBody>(i) == true)
		{
			
			PhysicsSystem::m_PhysicsBody_IDs.push_back(i); //Adds anything that I want to check for AABB to a vector
			ECS::Get<PhysicsBody>(i).Update(i);

		}
	}

	
	if (AABB(ECS::Get<PhysicsBody>(1), ECS::Get<PhysicsBody>(3)))
	{
		if (ECS::Get<PhysicsBody>(1).GetBodyType() == 1 && ECS::Get<PhysicsBody>(3).GetBodyType() == 0);
		{
			std::cout << "Dick and cock yep \n";
			ECS::Get<Transform>(1).SetPosition(ECS::Get<Transform>(1).GetPosition() - ECS::Get<PhysicsBody>(1).GetVelocity() * (Timer::dt * 2));
			
		}
	}
	
	
	

}

bool PhysicsSystem::AABB(PhysicsBody body1, PhysicsBody body2)
{
	if (body1.GetBox().m_MinX < body2.GetBox().m_MaxX && body1.GetBox().m_MaxX > body2.GetBox().m_MinX
		&& body1.GetBox().m_MinY < body2.GetBox().m_MaxY && body1.GetBox().m_MaxY > body2.GetBox().m_MinY
		&& body1.GetBox().m_MinZ < body2.GetBox().m_MaxZ && body1.GetBox().m_MaxZ > body2.GetBox().m_MinZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}
