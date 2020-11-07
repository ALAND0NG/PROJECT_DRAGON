#pragma once
#include <GLM/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "GLM/gtx/quaternion.hpp"



class Transform
{
public:
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::quat GetRotation();
	glm::mat4 GetTransform();

	void SetPosition(glm::vec3 pos);
	void SetScale(glm::vec3 sca);
	void SetRotation(glm::vec3 axis, float ammount);

	void SetModelMat(glm::mat4 modelmat);//physics engine will spit out a mat 4, we set it here every frame

	void ComputeGlobalMat(); //this is called everyframe from the backend

private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0f, 0.f, 0.f, 0.f);
	glm::mat4 modelMat = glm::mat4(1.0f); //Model matrix that is passed to the shader
};