#include "Camera.h"

Camera::Camera()
{
	this->cameraPosition = glm::vec3(0.0f,0.0f,0.0f);
	this->cameraTarget = glm::vec3(2.0f,2.0f,2.0f);
	this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getCamera()
{
	return(glm::lookAt(cameraPosition, cameraPosition + cameraTarget, Up));
}

glm::vec3 Camera::getCameraPosition()
{
	return (this->cameraPosition);
}

void Camera::toLeft()
{
	this->cameraPosition += (glm::normalize(glm::cross(cameraTarget, Up)));
}

void Camera::toRight()
{
	cameraPosition -= (glm::normalize(glm::cross(cameraTarget, Up)));
}

void Camera::toFront()
{
	cameraPosition += (glm::normalize(cameraTarget));
}

void Camera::toBack()
{
	cameraPosition -= (glm::normalize(cameraTarget));
}

void Camera::mouseMove(double new_x, double new_y, int width, int height)
{
	double angle_x = 3.14f;
	double angle_y = 0.0f;

	double speed = 0.009f;

	angle_x += speed * float(width / 2 - new_x);
	angle_y += speed * float(height / 2 - new_y);

	glm::vec3 direction(
		cos(angle_y) * sin(angle_x),
		sin(angle_y),
		cos(angle_y) * cos(angle_x)
	);

	glm::vec3 right = glm::vec3(
		sin(angle_x - 3.14f / 2.0f),
		0,
		cos(angle_x - 3.14f / 2.0f)
	);

	this->cameraTarget = direction;
	this->Up = glm::cross(right, direction);

}
