#include <Header/PhysicsSystem.h>

void PhysicsSystem::Update()
{
	auto reg = ECS::GetReg();

	for (int i = 0; i < reg->size(); i++)
	{
		if (ECS::Has<PhysicsBody>(i) == true)
		{
			
			ECS::Get<PhysicsBody>(i).Update(i);

			//if (AABB(ECS::Get<PhysicsBody>(1), 0, ECS::Get<PhysicsBody>(3), 0)) //Big temporary test
				//std::cout << "Colliding on x kek";
		}
	}
}

bool PhysicsSystem::AABB(PhysicsBody body1, int boxid1, PhysicsBody body2, int boxid2)
{
	if (body1.GetBox(boxid1).m_MinX <= body2.GetBox(boxid2).m_MaxX )
	{
		return true;
	}
	else
	{
		return false;
	}
}
