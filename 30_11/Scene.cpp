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

	this->pointLight = new PointLight();

	this->directionalLight = new DirectionalLight(glm::vec3(0.0f, 0.1f, 1.0f));
	this->directionalLight->setColor(glm::vec3(1.0f, 0.72f, 0.56f));

	this->spotLight = new SpotLight();
	this->spotLight->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
}

Scene::~Scene()
{
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
		obj->useShader();

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
			obj->getShader()->setVec3(this->pointLight->getPosition(), "lightPosition");
			
			this->sendLights(obj);

			obj->Draw(this->camera);
		}
		
		obj->getShader()->DeactivateProgram();	
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

void Scene::drawTextureObject(DrawableObject* obj)
{
	obj->getShader()->bindTexture(obj->getTextureID());

	obj->getShader()->setVec3(this->camera->getCameraPosition(), "viewPosition");
	obj->getShader()->setVec3(this->pointLight->getPosition(), "lightPosition");

	this->sendLights(obj);

	obj->Draw(this->camera);

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

	obj->getShader()->DeactivateProgram();
	am->unbindIBO();
	am->unbindVAO();


}

void Scene::sendLights(DrawableObject* obj)
{
	/*
	//PointLight
	this->pointLight->setPosition(glm::vec3(0.0f,1.0f,0.0f));
	obj->getShader()->setVec3(this->pointLight->getPosition(), "lights[0].position");
	//obj->getShader()->setVec3(this->pointLight->getColor(), "lights[0].color_of_light");
	obj->getShader()->setInt(1, "lights[0].type");
	*/

	//DirectionalLight
	obj->getShader()->setVec3(this->directionalLight->getDirection(), "lights[1].direction");
	obj->getShader()->setVec3(this->directionalLight->getColor(), "lights[1].color_of_light");
	obj->getShader()->setInt(2, "lights[1].type");
	

	//SpotLight
	this->spotLight->setPosition(this->camera->getCameraPosition());
	this->spotLight->setDirection(this->camera->getCameraDirection());

	obj->getShader()->setVec3(this->spotLight->getPosition(), "lights[2].position");
	obj->getShader()->setVec3(this->spotLight->getDirection(), "lights[2].direction");
	obj->getShader()->setFloat(this->spotLight->getCutOff(), "lights[2].cutOff");
	obj->getShader()->setFloat(this->spotLight->getOuterCutOff(), "lights[2].outer_cutOff");
	obj->getShader()->setFloat(this->spotLight->getConstant(), "lights[2].constant");
	obj->getShader()->setFloat(this->spotLight->getLinear(), "lights[2].linear");
	obj->getShader()->setFloat(this->spotLight->getQuadratic(), "lights[2].quadratic");
	obj->getShader()->setInt(3, "lights[2].type");
	
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this->camera->setCamera(position, target, up);
}







