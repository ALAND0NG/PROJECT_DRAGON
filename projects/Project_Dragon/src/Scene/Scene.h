#pragma once

#include "entt.hpp"
#include "Componenents.h"
#include "GLFW/glfw3.h"


class Scene
{
public:
	Scene();
	~Scene();
	
	
	
	void virtual InitScene(float windowWidth, float windowHeight)
	{
	}//this is where levels are built
	void virtual OnUpdate()
	{
	}//Scene specific update function
	entt::registry* GetSceneReg();
	GLFWwindow* GetWindow();
	
	template<typename T, typename... Args>
	T& AddComponent(Args&&... args, entt::entity ent)
	{
		return m_SceneReg->emplace<T>(ent, std::forward<Args>(args)...);
	}
	template<typename T>
	T& Get(entt::entity ent)
	{
		return m_SceneReg->get<T>(ent);
	}
	
protected:
	entt::registry* m_SceneReg; //this is not the main ecs, just declare it here
	GLFWwindow* m_Scenewindow; //Need a window so that on scene declare we can set the size
};