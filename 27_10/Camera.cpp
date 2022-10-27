#include "Camera.h"

Camera::Camera()
{
	this->shaders = std::vector<ShaderProgram*>();

	this->cameraPosition = glm::vec3(10.0f,0.0f,0.0f);
	this->cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
	this->Up = glm::vec3(0.0f, 0.0f, 0.0f);

	this->deltaTime = 0.0f;
	this->lastFrame = 0.0f;
	this->cameraSpeed = 0.0f;
}

void Camera::attachShader(ShaderProgram* shader)
{
	this->shaders.push_back(shader);
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
	this->cameraPosition -= this->getCameraSpeed() * (glm::normalize(glm::cross(cameraTarget, Up)));
}

void Camera::toRight()
{
	cameraPosition += this->getCameraSpeed() * (glm::normalize(glm::cross(cameraTarget, Up)));
}

void Camera::toFront()
{
	
	cameraPosition += this->getCameraSpeed() * (glm::normalize(cameraTarget));
}

void Camera::toBack()
{
	cameraPosition -= this->getCameraSpeed() * (glm::normalize(cameraTarget));
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

void Camera::updateDeltaTime()
{
	float currentFrame = static_cast<float>(glfwGetTime());

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

float Camera::getCameraSpeed()
{	
	this->cameraSpeed = 40.f * this->deltaTime;

	return this->cameraSpeed;
}
