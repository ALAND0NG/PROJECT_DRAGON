#include "Scene.h"


Scene::Scene()
{
	entt::registry tempReg;
	m_SceneReg = &tempReg;
}
Scene::~Scene()
{

}


entt::registry* Scene::GetSceneReg()
{
	return m_SceneReg;
}

GLFWwindow* Scene::GetWindow()
{
	return m_Scenewindow;
}
