#include "Scene.h"

Scene::Scene()
{
	this->objects = std::vector<DrawableObject*>();
	this->camera = new Camera();
	this->light = new Light();
}

Scene::~Scene()
{
	this->objects.clear();
	delete this->camera;
	delete this->light;
}

void Scene::addDrawableObject(DrawableObject* object)
{
	objects.push_back(object);
}

void Scene::drawScene(int width, int height)
{
	// UPDATE deltaTime per frame
	this->camera->updateDeltaTime();

	for (DrawableObject* obj : this->objects)
	{	
		// use current object shader
		obj->useShader();

		// Model
		obj->getShader()->setMatrix(obj->getModelMatrix(), "modelMatrix");

		// View
		obj->getShader()->setMatrix(this->camera->getCamera(), "viewMatrix");
		// Projection
		obj->getShader()->setMatrix(glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f), "projectionMatrix");

		// Light Position
		obj->getShader()->setVec3(this->getLightPosition(), "lightPosition");
		// View Position
		obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");

		// Draw current model
		obj->getModel()->drawModel();
	}

}

glm::vec3 Scene::getLightPosition()
{
	return this->light->getPosition();
}

Camera* Scene::getCamera()
{
	return this->camera;
}

