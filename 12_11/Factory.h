#pragma once

#include <map>
#include "DrawableObject.h"
#include "Scene.h"
#include "Models.h"

class Factory
{
private:
	static Factory* instance;
	Factory();
	std::map<string, Model*> models;

public:
	static Factory* GetInstance();

	DrawableObject* createObject(int shaderType, int modelType, glm::mat4 transformationMatrix);
	DrawableObject* createObjectTexture(glm::mat4 transformationMatrix, const char* textureName);

	Scene* createSpheresScene();
	Scene* createOneSphereScene();
	Scene* createMultipleObjectsScene();
	Scene* createTextureScene();
};