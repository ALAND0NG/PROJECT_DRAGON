#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>
float tempAspectRatio = 16 / 9;
Camera::Camera() :
	_nearPlane(0.1f),
	_farPlane(1000.0f),
	_fovRadians(glm::degrees(90.0f)),
	_aspectRatio(tempAspectRatio),
	_position(glm::vec3(0.0f)),
	_normal(glm::vec3(0.0f, 0.0f, 1.0f)),
	_up(glm::vec3(0.0f, -1.0f, 0.0f)), // Using Y-up coordinate system by default
	_view(glm::mat4(1.0f)),
	_projection(glm::mat4(1.0f)),
	_viewProjection(glm::mat4(1.0f)),
	_isOrtho(false),
	_orthoHeight(10),
	_isDirty(true)
{
	__CalculateProjection();
}


void Camera::SetIsOrtho(bool isOrtho) {
	_isOrtho = isOrtho;
	__CalculateProjection();
}

void Camera::SetOrthoHeight(float orthoHeight) {
	_orthoHeight = orthoHeight;
	__CalculateProjection();
}


void Camera::SetPosition(const glm::vec3& position) {
	_position = position;
	__CalculateView();
}

void Camera::SetForward(const glm::vec3& forward) {
	_normal = forward;
	__CalculateView();
}

void Camera::LookAt(const glm::vec3& point) {
	_normal = -glm::normalize(_position - point);
	__CalculateView();
}

void Camera::SetUp(const glm::vec3& up) {
	_up = up;
	__CalculateView();
}

void Camera::ResizeWindow(int windowWidth, int windowHeight) {
	_aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	__CalculateProjection();
}

void Camera::SetFovRadians(float value) {
	_fovRadians = value;
	__CalculateProjection();
}

void Camera::SetFovDegrees(float value) {
	SetFovRadians(glm::radians(value));
}

const glm::mat4& Camera::GetViewProjection() const {
	if (_isDirty) {
		_viewProjection = _projection * _view;
		_isDirty = false;
	}
	return _viewProjection;
}

void Camera::SetNear(float near)
{

	_nearPlane = near;
	__CalculateProjection();
}

void Camera::SetFar(float far)
{
	
		_farPlane = far;
		__CalculateProjection();
	
}

void Camera::SetProjection(glm::mat4 proj)
{
	_projection = proj;

	_isDirty = true;
}

void Camera::__CalculateProjection()
{
	if (_isOrtho) {
		_projection = glm::ortho(
			-_orthoHeight * _aspectRatio, _orthoHeight * _aspectRatio,
			-_orthoHeight, _orthoHeight,
			_nearPlane, _farPlane);
	}
	else {
		_projection = glm::perspective(_fovRadians, _aspectRatio, _nearPlane, _farPlane);
	}
	_isDirty = true;
}

void Camera::__CalculateView() {
	// TODO: implement
	_view = glm::lookAt(_position, _position + _normal, _up);
	_isDirty = true;
}
