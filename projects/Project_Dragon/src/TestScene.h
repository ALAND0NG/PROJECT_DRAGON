#pragma once
#include <ElementEngine.h>
#include <TestPrefab.h>
#include <StraightTrack.h>
#include <SideTrack.h>
#include <RightTurn.h>

class TestScene : public Scene
{
public:
	void InitScene() override;
	void Update() override;
private:
	entt::registry* m_sceneReg = nullptr;
};