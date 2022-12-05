#include "Scene.h"
#include "AssimpModel.h"


Scene::Scene()
{
	this->objects = std::vector<DrawableObject*>();
	this->camera = new Camera();

	this->constant = new ShaderProgram("ConstantShader.frag", "ConstantShader.vert");
	this->lambert = new ShaderProgram("LambertShader.frag", "LambertShader.vert");
	this->phong = new ShaderProgram("PhongShader.frag", "PhongShader.vert");
	this->blinnPhong = new ShaderProgram("BlinnPhongShader.frag", "BlinnPhongShader.vert");
	this->texture = new ShaderProgram("TextureShader.frag", "TextureShader.vert");
	this->skybox = new ShaderProgram("skybox.frag", "skybox.vert");
	this->lights = new ShaderProgram("PhongLightsShader.frag", "PhongShader.vert");
	this->assimp = new ShaderProgram("PhongLightsTextureShader.frag", "PhongLightsTextureShader.vert");

	this->constant->setObservedCamera(this->camera);
	this->lambert->setObservedCamera(this->camera);
	this->phong->setObservedCamera(this->camera);
	this->blinnPhong->setObservedCamera(this->camera);
	this->texture->setObservedCamera(this->camera);
	this->skybox->setObservedCamera(this->camera);
	this->lights->setObservedCamera(this->camera);
	this->assimp->setObservedCamera(this->camera);

	this->lightObjects = std::vector<Light*>();
}

Scene::~Scene()
{
	this->objects.clear();
	this->lightObjects.clear();

	delete this->skyboxObject;

	delete this->camera;

	delete this->constant;
	delete this->lambert;
	delete this->phong;
	delete this->blinnPhong;
	delete this->texture;
	delete this->skybox;
	delete this->lights;

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
	case 7:
		object->setShader(this->assimp);
		break;
	default:
		object->setShader(this->constant);
		
	}

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

		// use current object shader program
		obj->activateShader();

		// Texture
		if (obj->isTexture())
		{
			this->drawTextureObject(obj);
		}

		else if (obj->isAssimp())
		{
			this->drawAssimpObject(obj);
		}
		else
		{
			obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");
			/*
			PointLight* point = new PointLight();
			obj->getShader()->setVec3(point->getPosition(), "lightPosition");
			*/
			this->sendLights(obj);

			obj->draw(this->camera);
		}
		
		obj->getShader()->deactivateProgram();	
	}

}

void Scene::drawSkyBox()
{
	if (this->skyboxObject != nullptr)
	{
		this->skyboxObject->activateShader();

		this->skyboxObject->getTransformation()->translateMatrix(this->camera->getCameraPosition());

		this->skyboxObject->getShader()->bindSkyBox(this->skyboxObject->getTextureID());
		this->skyboxObject->draw(this->camera);
	}
}

void Scene::drawTextureObject(DrawableObject* obj)
{
	obj->getShader()->bindTexture(obj->getTextureID());

	obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");
	/*
	PointLight* point = new PointLight();
	obj->getShader()->setVec3(point->getPosition(), "lightPosition");
	*/

	this->sendLights(obj);

	obj->draw(this->camera);

}

void Scene::drawAssimpObject(DrawableObject* obj)
{

	AssimpModel* am = (AssimpModel*)obj->getModel();

	obj->getShader()->setMatrix(obj->getModelMatrix(), "modelMatrix");
	obj->getShader()->setMatrix(this->camera->getCamera(), "viewMatrix");
	obj->getShader()->setMatrix(this->camera->getProjectionMatrix(), "projectionMatrix");

	obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");

	am->bindVAO();
	am->bindIBO();

	obj->getShader()->bindTexture(am->getTextureID());

	this->sendLights(obj);


	obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");

	glDrawElements(GL_TRIANGLES, am->getIndices(), GL_UNSIGNED_INT, NULL);

	obj->getShader()->deactivateProgram();
	am->unbindIBO();
	am->unbindVAO();
}

void Scene::sendLights(DrawableObject* obj)
{
	int size = (int)this->lightObjects.size();
	
	obj->getShader()->setInt(size, "numOfLights");

	for (int i = 0; i < size; i++)
	{
		std::string name = "lights[" + std::to_string(i) + "]";
		int type = this->lightObjects[i]->getType();
		if (type == 1)
		{
			PointLight* p = (PointLight*)this->lightObjects[i];

			obj->getShader()->setVec3(p->getPosition(), (name + ".position").c_str());
			obj->getShader()->setInt(p->getType(), (name + ".type").c_str());
		}
		else if (type == 2)
		{
			DirectionalLight* d = (DirectionalLight*)this->lightObjects[i];
			obj->getShader()->setVec3(d->getDirection(), (name + ".direction").c_str());
			obj->getShader()->setVec3(d->getColor(), (name + ".color_of_light").c_str());
			obj->getShader()->setInt(d->getType(), (name + ".type").c_str());
		}
		else if (type == 3)
		{
			SpotLight* s = (SpotLight*)this->lightObjects[i];
			s->setPosition(this->camera->getCameraPosition());
			s->setDirection(this->camera->getCameraDirection());

			obj->getShader()->setVec3(s->getPosition(), (name + ".position").c_str());
			obj->getShader()->setVec3(s->getDirection(), (name + ".direction").c_str());
			obj->getShader()->setFloat(s->getCutOff(), (name + ".cutOff").c_str());
			obj->getShader()->setFloat(s->getOuterCutOff(), (name + ".outer_cutOff").c_str());
			obj->getShader()->setFloat(s->getConstant(), (name + ".constant").c_str());
			obj->getShader()->setFloat(s->getLinear(), (name + ".linear").c_str());
			obj->getShader()->setFloat(s->getQuadratic(), (name + ".quadratic").c_str());
			obj->getShader()->setInt(s->getType(), (name + ".type").c_str());
		}
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
	this->lightObjects.push_back(light);
}







