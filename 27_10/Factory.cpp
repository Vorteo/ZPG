#include "Factory.h"

Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

DrawableObject* Factory::createSphereObject(int shaderType, int modelType, glm::mat4 transformationMatrix)
{
	const char* vertex;
	const char* fragment;

	switch (shaderType) {
	case 1:
		vertex = "LambertShader.vert";
		fragment = "LambertShader.frag";
		break;
	case 2:
		vertex = "PhongShader.vert";
		fragment = "PhongShader.frag";
		break;
	case 3:
		vertex = "BlinnPhongShader.vert";
		fragment = "BlinnPhongShader.frag";
		break;
	default:
		vertex = "ConstantShader.vert";
		fragment = "ConstantShader.frag";
	}

	switch (modelType)
	{
	case 1:
		return new DrawableObject(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])), new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
	case 2:
		return new DrawableObject(new Model(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0])), new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
	}

}

Scene* Factory::createSpheresScene()
{
	Scene* scene = new Scene();

	scene->addDrawableObject(this->createSphereObject(1, 1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createSphereObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))));
	scene->addDrawableObject(this->createSphereObject(3, 1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createSphereObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))));
	
	return scene;
}
Scene* Factory::createOneSphereScene()
{
	Scene* scene = new Scene();


	scene->addDrawableObject(this->createSphereObject(2,2, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))));

	return scene;
}
Scene* Factory::createMultipleObjectsScene()
{
	Scene* scene = new Scene();

	for (int i = 0; i < 101; i++)
	{
		//scene->addDrawableObject();

	}

	return scene;
}
