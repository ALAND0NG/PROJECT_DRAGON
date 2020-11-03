#pragma once
#include <ECS.h>
#include <Timer.h>
#include <BackEnd.h>
class Scene
{
public:
	Scene()
	{
		
	}

	virtual void InitScene();

	virtual void Update();


private:
	entt::registry* m_sceneReg = nullptr;
};