#include "Transformation.h"

Transformation::Transformation()
{
	this->modelMatrix = glm::mat4(1.0f);
}

void Transformation::scaleModel(glm::vec3 ratio)
{
	this->modelMatrix = glm::scale(glm::mat4(1.0f), ratio);
}

void Transformation::translateModel(glm::vec3 translation)
{
	this->modelMatrix = glm::translate(glm::mat4(1.0f), translation);
}

void Transformation::rotateModel(glm::vec3 axis)
{
	this->modelMatrix = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), axis);
}
