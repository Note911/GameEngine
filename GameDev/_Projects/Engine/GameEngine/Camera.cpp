#include "Camera.h"
#include <iostream>


Camera::Camera() :
_projectionMatrix(1.0f),
_scale(1.0f),
_needsMatrixUpdate(true),
_screenWidth(500),
_screenHeight(500)
{
	_transform = Transform();
	_transform.setPosition(glm::vec3(0, 0, 0));
	_transform.setRotation(glm::vec4(0, 0, 0, 1));
	_transform.setScale(glm::vec3(1, 1, 1));
}


Camera::~Camera()
{
}

void Camera::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

void Camera::update() {
	if (_needsMatrixUpdate) {
		_transform.updateTransform(glm::mat4(1.0f));
		glm::mat4 projMatrix = glm::perspective(45.0f, (float)(_screenWidth / _screenHeight), 1.0f, 1000.0f);

		glm::vec4 forward = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
		glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

		glm::vec4 rotation = _transform.getRotation();
		glm::vec4 inverseRotation = glm::vec4(-rotation.x, -rotation.y, -rotation.z, rotation.w);

		//forward = rotation * forward;
		//up = rotation * up;

		glm::mat4 modelViewMatrix = glm::lookAt(_transform.getPosition(), glm::vec3(forward.x, forward.y, forward.z), glm::vec3(up.x, up.y, up.z));

		std::cout << "Rotation: "<< rotation.x << " " << rotation.y << " " << rotation.z << " " << rotation.w << "\n";
		std::cout << "Forward: " << forward.x << " " << forward.y << " " << forward.z << " " << forward.w <<"\n";

		_projectionMatrix = projMatrix * modelViewMatrix;
		
		_needsMatrixUpdate = false;
	}
}

