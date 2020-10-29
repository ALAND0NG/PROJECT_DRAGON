#pragma once
#include <Header/Scene.h>
class TankScene : public Scene
{
public:
	void InitScene()override;
	void Update() override;
private:
	entt::registry* m_sceneReg = nullptr;
};
