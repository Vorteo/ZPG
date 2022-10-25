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
};