#pragma once
#include "Headers.h"

class Transformation
{
protected:
	glm::mat4 M = glm::mat4(1.0f);

public:
	Transformation();
	Transformation(glm::mat4 transformationMatrix);
	~Transformation();
	glm::mat4 getTransformationMatrix();
	void setTransform(glm::mat4 matrix);

	void scaleMatrix(glm::vec3 ratio);
	void rotateMatrix(float degree, glm::vec3 axis);
	void translateMatrix(glm::vec3 translation);
};