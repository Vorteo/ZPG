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
	int i = 0;

	for (Model* model : this->models)
	{
		glm::mat4 M = model->getModelMatrix();
	    /*
		M = glm::scale(M, glm::vec3(0.7f));
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
		M = glm::rotate(M, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		*/

		if (i == 0)
		{
			M = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
			model->setModelMatrix(M);
		}
		if (i == 1)
		{
			M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
		}
		if (i == 2)
		{
			M = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
		}
		if(i == 3)
		{
			M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
		}

		GLint idModelTransform = program->getModelMatrix();
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

		model->drawModel();

		i++;
		M = glm::mat4(1.0f);
	}

}

void Scene::setModelMatrixOfModel(glm::mat4 modelMatrix, int i)
{
	this->models[i]->setModelMatrix(modelMatrix);
}

