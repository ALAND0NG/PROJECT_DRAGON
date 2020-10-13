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

	void ComputeGlobalMat(); //this is called everyframe from the backend

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 globalMat;
};