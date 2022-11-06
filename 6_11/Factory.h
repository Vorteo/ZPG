#pragma once

#include "DrawableObject.h"
#include "Scene.h"
#include "Models.h"

class Factory
{
private:
	static Factory* instance;

public:
	static Factory* GetInstance();

	DrawableObject* createObject(int shaderType, int modelType, glm::mat4 transformationMatrix);

	Scene* createSpheresScene();
	Scene* createOneSphereScene();
	Scene* createMultipleObjectsScene();
};