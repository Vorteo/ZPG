#pragma once
#ifndef FACTORY_H
#define FACTORY_H
#include "DrawableObject.h"
#include "Scene.h"
#include <map>

class Factory
{
private:
	static Factory* instance;
	Factory();

	std::map<string, Model*> models;

public:
	static Factory* getInstance();

	DrawableObject* createObject(int modelType, glm::mat4 transformationMatrix);
	DrawableObject* createPlaineObjectWithTexture(glm::mat4 transformationMatrix, const char* textureName);
	DrawableObject* createSkyBoxObject();
	DrawableObject* createAssimpObject(std::string filePath, const char* textureName, glm::mat4 transformationMatrix);

	void addTreeOnPosition(Scene* scene, glm::vec3 pos);

	Scene* createSpheresScene();
	Scene* TestLightsScene();
	Scene* createMultipleObjectsScene();
	Scene* createSkyBoxScene();
	Scene* createComplexScene();
};
#endif