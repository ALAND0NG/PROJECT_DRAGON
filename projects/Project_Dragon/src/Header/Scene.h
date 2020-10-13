#pragma once
#include <Header/ECS.h>
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