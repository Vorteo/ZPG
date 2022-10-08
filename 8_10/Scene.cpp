#include "Scene.h"

Scene::Scene()
{
	this->models = std::vector<Model*>();
}

Scene::~Scene()
{
	this->models.clear();
}

void Scene::addModel(Model* model)
{
	this->models.push_back(model);
}

void Scene::drawScene(ShaderProgram* program)
{
	for (Model* model : this->models)
	{
		glm::mat4 M = model->getModelMatrix();

		M = glm::scale(M, glm::vec3(0.7f));
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
		M = glm::rotate(M, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		GLint idModelTransform = program->getModelMatrix();
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

		model->drawModel();
	}

}

