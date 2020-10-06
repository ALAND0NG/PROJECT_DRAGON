#include "Header/Scene.h"

void Scene::InitScene()
{
	//test stuff
	ecs->Create(0);
	ecs->Add<Camera>(0); //main player camera
	
}

void Scene::Update()
{
	
}