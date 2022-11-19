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

void Transformation::setTransform(glm::mat4 matrix)
{
	this->M = matrix;
}

void Transformation::scaleMatrix(glm::vec3 ratio)
{
	this->M = glm::scale(this->M, ratio);
}
void Transformation::rotateMatrix(float degree, glm::vec3 axis)
{
	this->M = glm::rotate(this->M, glm::radians(degree), axis);
}

void Transformation::translateMatrix(glm::vec3 translation)
{
	this->M = glm::translate(this->M, translation);
}
