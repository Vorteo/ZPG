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

	// Subject
	std::vector<ShaderProgram*> shaders;
	glm::mat4 changedMatrixValue = glm::mat4(1.0f);
	const char* changedMatrixName = nullptr;

public:
	Camera();

	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

	glm::mat4 getCamera();
	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();

	void updatePerspective(int width, int height);
	glm::mat4 getProjectionMatrix();

	void toLeft();
	void toRight();
	void toFront();
	void toBack();
	void mouseMove(double new_x, double new_y, int width, int height);
	void updateDeltaTime();
	float getCameraSpeed();

	// Subject methods	
 	void attachShader(ShaderProgram* shader);
	bool findShader(ShaderProgram* shader);
	void setChanges(glm::mat4 matrixValue, const char* matrixName);
	void notify();
	void update();

};
#endif