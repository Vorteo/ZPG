#include "Scene.h"

Scene::Scene()
{
	//this->manager = new DrawableObjectManager();
	this->objects = std::vector<DrawableObject*>();
	this->camera = new Camera();

	this->constant = new ShaderProgram("ConstantShader.frag", "ConstantShader.vert");
	this->lambert = new ShaderProgram("LambertShader.frag", "LambertShader.vert");
	this->phong = new ShaderProgram("PhongShader.frag", "PhongShader.vert");
	this->blinnPhong = new ShaderProgram("BlinnPhongShader.frag", "BlinnPhongShader.vert");
	this->texture = new ShaderProgram("TextureShader.frag", "TextureShader.vert");
	this->skybox = new ShaderProgram("skybox.frag", "skybox.vert");
	this->lights = new ShaderProgram("PhongLightsShader.frag", "PhongShader.vert");

	this->constant->setObservedCamera(this->camera);
	this->lambert->setObservedCamera(this->camera);
	this->phong->setObservedCamera(this->camera);
	this->blinnPhong->setObservedCamera(this->camera);
	this->texture->setObservedCamera(this->camera);
	this->skybox->setObservedCamera(this->camera);
	this->lights->setObservedCamera(this->camera);

	this->pointLight = new PointLight();
	this->directionalLight = new DirectionalLight(glm::vec3(0.0f, 0.0f, 1.0f));

	this->spotLight = new SpotLight();
	this->spotLight->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	this->ligtsObjects = std::vector<Light*>();
}

Scene::~Scene()
{
	//delete this->manager;
	delete this->skyboxObject;

	delete this->camera;

	delete this->constant;
	delete this->lambert;
	delete this->phong;
	delete this->blinnPhong;
	delete this->texture;
	delete this->skybox;
	delete this->lights;

	delete this->pointLight;
	delete this->directionalLight;
	delete this->spotLight;

}

void Scene::addDrawableObject(DrawableObject* object, int shaderType)
{
	switch (shaderType) {
	case 1:
		object->setShader(this->lambert);
		break;
	case 2:
		object->setShader(this->phong);
		break;
	case 3:
		object->setShader(this->blinnPhong);
		break;
	case 4:
		object->setShader(this->texture);
		break;
	case 5:
		object->setShader(this->skybox);
		break;
	case 6:
		object->setShader(this->lights);
		break;
	default:
		object->setShader(this->constant);
		
	}

	//this->manager->addDrawableObject(object);
	this->objects.push_back(object);
}

void Scene::setSkybox(DrawableObject* object)
{
	object->setShader(this->skybox);
	this->skyboxObject = object;
}


void Scene::drawScene(int width, int height)
{
	// UPDATE deltaTime per frame
	this->camera->updateDeltaTime();

	for (DrawableObject* obj : this->objects)
	{
		glStencilFunc(GL_ALWAYS, obj->getID(), 0xFF);

		//obj->setShader(this->lights);
		// use current object shader program
		obj->useShader();

		// Texture
		if (obj->isTexture())
		{
			obj->getShader()->bindTexture(obj->getTextureID());
		}

		//PointLight	
		/*
		obj->getShader()->setVec3(this->pointLight->getPosition(), "lights[0].position");
		obj->getShader()->setInt(1, "lights[0].type");
				
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
		obj->Draw(this->camera);
	}

}

void Scene::drawSkyBox()
{
	if (this->skyboxObject != nullptr)
	{
		this->skyboxObject->useShader();

		this->skyboxObject->getTransformation()->translateMatrix(this->camera->getCameraPosition());

		this->skyboxObject->getShader()->bindSkyBox(this->skyboxObject->getTextureID());
		this->skyboxObject->Draw(this->camera);
	}
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this->camera->setCamera(position, target, up);
}

void Scene::addLight(Light* light)
{
	this->ligtsObjects.push_back(light);
}







