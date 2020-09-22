#pragma once
#include "Scene/Scene.h"
#include "Game.h"

class TestScene : public Scene
{
	//TestScene();
	void InitScene(float windowWidth, float windowHeight) override;
	void OnUpdate() override;

};