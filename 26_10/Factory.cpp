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

Factory::~Factory()
{
}

DrawableObject Factory::createObject(int shaderType)
{
	switch (shaderType) {
	case 1:
		// lambert
		break;
	case 2:
		// phong shader
		break;
	case 3:
		// phong blinn shader
		break;
	default:
		// konstantni shader
	}

	return DrawableObject(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])), new ShaderProgram(), new Transformation());
}
