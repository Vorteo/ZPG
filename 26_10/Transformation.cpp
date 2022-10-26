#include "Transformation.h"

Transformation::Transformation(glm::mat4 transformationMatrix)
{
	this->M = transformationMatrix;
}

Transformation::~Transformation()
{
}

glm::mat4 Transformation::getTransformationMatrix()
{
	return this->M;
}