#include <Transform.h>
#include <GLM/matrix.hpp>
#include <GLM/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

glm::quat Transform::GetRotation()
{
	return rotation;
}

glm::mat4 Transform::GetTransform()
{
	return modelMat;
}

void Transform::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Transform::SetScale(glm::vec3 sca)
{
	scale = sca;
}

void Transform::SetRotation(glm::vec3 axis, float ammount)
{
	rotation = glm::rotate(modelMat,ammount, axis);
}

void Transform::SetModelMat(glm::mat4 modelmat)
{
	modelMat = modelmat;
}

void Transform::ComputeGlobalMat()
{
	modelMat = glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
}
