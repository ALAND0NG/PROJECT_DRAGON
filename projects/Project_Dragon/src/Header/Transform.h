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
	void SetRotation(glm::quat rot);

	void ComputeGlobalMat(); //this is called everyframe from the backend

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 modelMat = glm::mat4(1.0f); //Model matrix that is passed to the shader
};