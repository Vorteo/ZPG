#include "Scene.h"

Scene::Scene()
{
	this->models = std::vector<Model*>();
	this->camera = new Camera();
}

Scene::~Scene()
{
	this->models.clear();
	delete this->camera;
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
		
		//	M = glm::scale(M, glm::vec3(0.7f));
		//	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
		//	M = glm::rotate(M, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));

		GLint idModelTransform = program->getModelMatrix();
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

		model->drawModel();
	}

}

void Scene::setModelMatrixOfModel(glm::mat4 modelMatrix, int i)
{
	this->models[i]->setModelMatrix(modelMatrix);
}

