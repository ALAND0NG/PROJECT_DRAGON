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

	void InitScene();

	void Update();


private:
	entt::registry* m_sceneReg = nullptr;
};