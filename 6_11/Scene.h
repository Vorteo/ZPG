#pragma once

#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "DrawableObject.h"

#include<vector>

class Scene 
{
private:
	std::vector<DrawableObject*> objects;
	Camera* camera;

	PointLight* pointLight;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;

public:
	Scene();
	~Scene();

	void addDrawableObject(DrawableObject* object);
	void drawScene(int width, int height);

	glm::vec3 getLightPosition();
	Camera* getCamera();
};