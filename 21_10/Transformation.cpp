#include "Transformation.h"

Transformation::Transformation()
{
	this->M = glm::mat4(1.0f);
}

void Transformation::scaleModel(glm::vec3 ratio)
{
	this->M = glm::scale(glm::mat4(1.0f), ratio);
}

void Transformation::translateModel(glm::vec3 translation)
{
	this->M = glm::translate(glm::mat4(1.0f), translation);
}

void Transformation::rotateModel(glm::vec3 axis)
{
	this->M = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), axis);
}
