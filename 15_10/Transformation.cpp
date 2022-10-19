#include "Transformation.h"

Transformation::Transformation()
{
	this->Matrix = glm::mat4(1.0f);
}

void Transformation::scaleModel(glm::vec3 ratio)
{
	this->Matrix = glm::scale(glm::mat4(1.0f), ratio);
}

void Transformation::translateModel(glm::vec3 translation)
{
	this->Matrix = glm::translate(glm::mat4(1.0f), translation);
}

void Transformation::rotateModel(glm::vec3 axis)
{
	this->Matrix = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), axis);
}

glm::mat4 Transformation::getMatrix()
{
	return (this->Matrix);
}
