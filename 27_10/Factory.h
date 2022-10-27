#pragma once
#ifndef FACTORY_H
#define FACTORY_H
#include "DrawableObject.h"
#include "Scene.h"
#include "Models.h"

class Factory
{
private:
	static Factory* instance;
public:
	static Factory* GetInstance();
	DrawableObject* createSphereObject(int shaderType, int modelType, glm::mat4 transformationMatrix);
	Scene* createSpheresScene();
	Scene* createOneSphereScene();
	Scene* createMultipleObjectsScene();
};
#endif