#pragma once
#include <Header/ECS.h>
class Scene
{
public:
	Scene(ECS* SetEcs)
	{
		ecs = SetEcs;
	}

	void InitScene();

	void Update();


private:
	ECS* ecs; //pointer to the ECS
};