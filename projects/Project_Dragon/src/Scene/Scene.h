#pragma once

#include "Componenents.h"
#include "GLFW/glfw3.h"
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();
	
	Entity CreateEntity();
	
	virtual void InitScene(float windowWidth, float windowHeight); //this is where levels are built
	virtual void OnUpdate(); //Scene specific update function
	entt::registry* GetSceneReg();
	GLFWwindow* GetWindow();
	
	template<typename T, typename... Args>
	T& Add(Args&&... args, entt::entity ent)
	{
		return ecs.emplace<T>(ent, std::forward<Args>(args)...);
	}
	
protected:
	entt::registry* m_SceneReg; //this is not the main ecs, just declare it here
	GLFWwindow* m_Scenewindow; //Need a window so that on scene declare we can set the size
};