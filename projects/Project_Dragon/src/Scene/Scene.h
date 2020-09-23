#pragma once
#include <iostream> //just for debug
#include "ECS/Entity.h"
#include "ecs/Components.h"
#include "GLFW/glfw3.h"
#include <string>


class Entity;

class Scene
{
public:
	Scene();
	~Scene();
	
	Entity CreateEntity(const std::string& name = std::string());
	
	void virtual InitScene()
	{
	}//this is where levels are built
	void virtual OnUpdate()
	{
	}//Scene specific update function

	entt::registry* GetSceneReg();
	GLFWwindow* GetWindow();
	
	
	bool GetClose()
	{
		return ShouldClose;
	}

private:
	entt::registry* m_SceneReg; //ECS will be Scene by Scene
	GLFWwindow* m_Scenewindow; //Need a window so that on scene declare we can set the size
	bool ShouldClose = 0;
	
	friend class Entity;
	friend class TestScene;

};