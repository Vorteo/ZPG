#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "ShaderProgram.h"

class ShaderProgram;
class Camera 
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 Up;

	float deltaTime;
	float lastFrame;
	float cameraSpeed;

	std::vector<ShaderProgram*> shaders;
public:
	Camera();

	void attachShader(ShaderProgram* shader);
	void notify();
	void update();

	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	glm::mat4 getCamera();
	glm::vec3 getCameraPosition();

	void toLeft();
	void toRight();
	void toFront();
	void toBack();

	void mouseMove(double new_x, double new_y, int width, int height);
	void updateDeltaTime();
	float getCameraSpeed();
};
#endif