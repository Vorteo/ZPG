#include "Scene.h"

Scene::Scene()
{
	this->objects = std::vector<DrawableObject*>();
	this->camera = new Camera();

	this->constant = new ShaderProgram("ConstantShader.frag", "ConstantShader.vert");
	this->lambert = new ShaderProgram("LambertShader.frag", "LambertShader.vert");
	this->phong = new ShaderProgram("PhongShader.frag", "PhongShader.vert");
	this->blinnPhong = new ShaderProgram("BlinnPhongShader.frag", "BlinnPhongShader.vert");
	this->texture = new ShaderProgram("TextureShader.frag", "TextureShader.vert");

	this->constant->setObservedCamera(this->camera);
	this->lambert->setObservedCamera(this->camera);
	this->phong->setObservedCamera(this->camera);
	this->blinnPhong->setObservedCamera(this->camera);
	this->texture->setObservedCamera(this->camera);

	this->pointLight = new PointLight();
	this->directionalLight = new DirectionalLight(glm::vec3(0.0f, 0.0f, 1.0f));
	this->spotLight = new SpotLight(glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 5.0f, 0.0f));

}

Scene::~Scene()
{
	this->objects.clear();

	delete this->camera;

	delete this->constant;
	delete this->lambert;
	delete this->phong;
	delete this->blinnPhong;

	delete this->pointLight;
	delete this->directionalLight;
	delete this->spotLight;

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
		//obj->setShader(this->phong);
		
		// use current object shader
		obj->useShader();

		// Model
		obj->getShader()->setMatrix(obj->getModelMatrix(), "modelMatrix");
		// View
		obj->getShader()->setMatrix(this->camera->getCamera(), "viewMatrix");
		// Projection
		obj->getShader()->setMatrix(glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f), "projectionMatrix");

		// Texture
		obj->getShader()->bindTexture(obj->getTextureID());
		//obj->getShader()->bindSkyBox(obj->getTextureID());

		//PointLight	
		obj->getShader()->setVec3(this->pointLight->getPosition(), "lights[0].position");
		obj->getShader()->setInt(1, "lights[0].type");
		
		/*
		//DirectionalLight
		obj->getShader()->setVec3(this->directionalLight->getDirection(), "lights[1].direction");
		obj->getShader()->setInt(2, "lights[1].type");
		
		//SpotLight
		
		obj->getShader()->setVec3(this->spotLight->getPosition(), "lights[2].position");
		obj->getShader()->setVec3(this->spotLight->getDirection(), "lights[2].direction");
		obj->getShader()->setFloat(this->spotLight->getCutOff(), "lights[2].cutOff");
		obj->getShader()->setInt(3, "lights[2].type");
		*/

		// View Position
		obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");

		// Draw current model
		obj->Draw();
	}

}

glm::vec3 Scene::getLightPosition()
{
	return this->pointLight->getPosition();
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this->camera->setCamera(position, target, up);
}





