#include "Factory.h"
#include "Models/sphere.h"

Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

DrawableObject* Factory::createSphereObject(int shaderType)
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

	return new DrawableObject(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])), new ShaderProgram(fragment, vertex), new Transformation());
}

Scene* Factory::createSpheresScene()
{
	Scene* scene = new Scene();

	scene->addDrawableObject(this->createSphereObject(0));
	scene->addDrawableObject(this->createSphereObject(1));
	scene->addDrawableObject(this->createSphereObject(2));
	scene->addDrawableObject(this->createSphereObject(3));

	return scene;
}
