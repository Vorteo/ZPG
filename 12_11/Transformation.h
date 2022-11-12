#pragma once
#include "Headers.h"

class Transformation
{
protected:
	glm::mat4 M;

public:
	Transformation(glm::mat4 transformationMatrix = glm::mat4(1.0f));
	~Transformation();
	glm::mat4 getTransformationMatrix();

	void scaleMatrix(glm::vec3 ratio);
	void rotateMatrix(float degree, glm::vec3 axis);
	void translateMatrix(glm::vec3 translation);
};