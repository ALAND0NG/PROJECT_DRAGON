#pragma once
#include <Header/ECS.h>
#include <Header/Timer.h>
#include <Header/BackEnd.h>
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