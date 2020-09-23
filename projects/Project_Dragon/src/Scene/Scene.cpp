#include "Scene.h"


Scene::Scene()
{
}
Scene::~Scene()
{

}

Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity(m_SceneReg->create(), this);
	return entity;
}


entt::registry* Scene::GetSceneReg()
{
	return m_SceneReg;
}

GLFWwindow* Scene::GetWindow()
{
	return m_Scenewindow;
}
