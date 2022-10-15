#include "Transformation.h"

Transformation::Transformation()
{
	this->M = glm::mat4(1.0f);
}

glm::mat4 Transformation::scaleModel()
{
	this->M = glm::scale(M, glm::vec3(0.7f));

	return M;
}

glm::mat4 Transformation::translateModel()
{
	this->M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));

	return M;
}

glm::mat4 Transformation::rotateModel()
{
	this->M = glm::rotate(M, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	return M;
}
