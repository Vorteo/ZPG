#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Headers.h"
#include "ShaderProgram.h"

class ShaderProgram;
class Camera
{
private:
	std::vector<ShaderProgram*> shaders;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 Up;

	float deltaTime;
	float lastFrame;
	float cameraSpeed;

public:
	Camera();

	void attachShader(ShaderProgram* shader);

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