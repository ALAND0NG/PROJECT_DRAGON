#pragma once
#include "Scene/Scene.h"
#include "Game.h"

class TestScene : public Scene
{
public:
	//TestScene();
	void InitScene() override;
	void OnUpdate() override;
private:
	//Any ECS component that should be used outside of the InitScene should be added here.
	Entity m_testEnt;

};