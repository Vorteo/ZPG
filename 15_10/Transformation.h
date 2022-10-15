#pragma once
#include "Headers.h"

class Transformation
{
private:
	glm::mat4 M = glm::mat4(1.0f);

public:
	Transformation();

	glm::mat4 scaleModel();
	glm::mat4 translateModel();
	glm::mat4 rotateModel();
};