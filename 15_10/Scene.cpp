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
	glm::mat4 Mat1 = glm::rotate(glm::mat4(1.0f), (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f , 1.0f));

	// parameters for rotate, scale, translate
	glm::vec3 ratio = glm::vec3(0.7f);
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 translation = glm::vec3(2.0f, 0.0f, 0.0f);

	for (Model* model : this->models)
	{
		model->setModelMatrix(Mat1);
		glm::mat4 M = model->getModelMatrix();

		/* 
		model->scaleModel(ratio);
		model->translateModel(translation);
		model->rotateModel(axis);
		M = model->getModelMatrix();
		*/

		GLint idModelTransform = program->getModelMatrix();
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

		model->drawModel();
	}

}

void Scene::setModelMatrixOfModel(glm::mat4 modelMatrix, int i)
{
	this->models[i]->setModelMatrix(modelMatrix);
}

