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
	
	//for (int i = 0; i < PhysicsSystem::m_PhysicsBody_IDs.size() - 1; i++)
	//{
		//for (int ix = 0; ix < PhysicsSystem::m_PhysicsBody_IDs.size() - 1; ix++)
		//{
			//writes the bodies once so I don't have to ECSet a million fucking times
			PhysicsBody b1, b2;
			b1 = ECS::Get<PhysicsBody>(1);
			b2 = ECS::Get<PhysicsBody>(6);
			
			if (AABB(b1,b2))
			{
				if (b1.GetBodyType() == 1 && b2.GetBodyType() == 0)
				{
					b1.ApplyForce(-b2.GetDeltaForce());
					b1.SetPosition(b1.GetPosition() - b1.GetVelocity() * 2.f);
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
