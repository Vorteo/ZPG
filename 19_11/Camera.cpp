#include "Camera.h"

Camera::Camera()
{
	this->projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	this->viewMatrix = glm::mat4(1.0f);

	this->shaders = std::vector<ShaderProgram*>();

	this->cameraPosition = glm::vec3(0.0f,0.0f,0.0f);
	this->cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
	this->Up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->deltaTime = 0.0f;
	this->lastFrame = 0.0f;
	this->cameraSpeed = 0.0f;
}

void Camera::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this->cameraPosition = position;
	this->cameraTarget = target;
	this->Up = up;
}

glm::mat4 Camera::getCamera()
{
	this->viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraTarget, Up);
	this->setChanges(this->viewMatrix, "viewMatrix");

	return this->viewMatrix;
}

glm::vec3 Camera::getCameraPosition()
{
	return (this->cameraPosition);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}

void Camera::toLeft()
{
	this->cameraPosition -= this->getCameraSpeed() * (glm::normalize(glm::cross(cameraTarget, Up)));
	this->getCamera();
}

void Camera::toRight()
{
	cameraPosition += this->getCameraSpeed() * (glm::normalize(glm::cross(cameraTarget, Up)));
	this->getCamera();
}

void Camera::toFront()
{
	
	cameraPosition += this->getCameraSpeed() * (glm::normalize(cameraTarget));
	this->getCamera();
}

void Camera::toBack()
{
	cameraPosition -= this->getCameraSpeed() * (glm::normalize(cameraTarget));
	this->getCamera();
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

	this->getCamera();
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

void Camera::attachShader(ShaderProgram* shader)
{
	this->shaders.push_back(shader);
}

bool Camera::findShader(ShaderProgram* shader)
{
	if (std::find(shaders.begin(), shaders.end(), shader) != shaders.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Camera::setChanges(glm::mat4 matrixValue, const char* matrixName)
{
	this->changedMatrixName = matrixName;
	this->changedMatrixValue = matrixValue;
	this->notify();
}

void Camera::notify()
{
	for (ShaderProgram* sp : shaders)
	{
		sp->update(this->changedMatrixValue, this->changedMatrixName);
	}
}

void Camera::update()
{
	this->setChanges(this->projectionMatrix, "projectionMatrix");
	this->getCamera();
}
