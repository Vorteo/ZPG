#pragma once
#ifndef FACTORY_H
#define FACTORY_H
#include "DrawableObject.h"
#include "Scene.h"

class Factory
{
private:
	static Factory* instance;
public:
	static Factory* GetInstance();
	DrawableObject* createSphereObject(int shaderType);
	Scene* createSpheresScene();
};
#endif