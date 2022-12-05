#include "Transformation.h"

Transformation::Transformation()
{
	this->M = glm::mat4(1.0f);
}

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

void Transformation::setTransformationMatrix(glm::mat4 matrix)
{
	this->M = matrix;
}

void Transformation::scaleMatrix(glm::vec3 ratio)
{
	this->M = glm::scale(glm::mat4(1.0f), ratio);
}
void Transformation::rotateMatrix(float degree, glm::vec3 axis)
{
	this->M = glm::rotate(glm::mat4(1.0f), glm::radians(degree), axis);
}

void Transformation::translateMatrix(glm::vec3 translation)
{	
	this->M = glm::mat4(1.0f);
	this->M = glm::translate(this->M, translation);
}
