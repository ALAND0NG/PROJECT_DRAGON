#include "Scene.h"


Scene::Scene()
{
	
	
}
Scene::~Scene()
{

}

Entity Scene::CreateEntity()
{
	return Entity(m_SceneReg->create());
}

entt::registry* Scene::GetSceneReg()
{
	return m_SceneReg;
}

GLFWwindow* Scene::GetWindow()
{
	return m_Scenewindow;
}
