#pragma once
#include "Headers.h"

class Transformation
{
protected:
	glm::mat4 Matrix;

public:
	Transformation();

	void scaleModel(glm::vec3 ratio);
	void translateModel(glm::vec3 translation);
	void rotateModel(glm::vec3 axis);

	glm::mat4 getMatrix();

};