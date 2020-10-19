#include <Header/Transform.h>
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

void Transform::SetRotation(glm::quat rot)
{
	rotation = rot;
}

void Transform::ComputeGlobalMat()
{
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 translateMatrix = glm::translate(position);

	modelMat = translateMatrix * glm::toMat4(rotation) * scaleMatrix;

}
