#include "Header/Scene.h"

void Scene::InitScene()
{
	
	ecs->Create(0);
	ecs->Add<TestComponent>(0);

}

void Scene::Update()
{
	std::cout << ecs->Get<TestComponent>(0).lol;
}