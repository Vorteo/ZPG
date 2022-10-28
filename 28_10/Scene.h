#pragma once

#include "Camera.h"
#include "Light.h"
#include "DrawableObject.h"

#include<vector>

class Scene 
{
private:
	std::vector<DrawableObject*> objects;
	Camera* camera;
	Light* light;

public:
	Scene();
	~Scene();

	void addDrawableObject(DrawableObject* object);
	void drawScene(int width, int height);

	glm::vec3 getLightPosition();
	Camera* getCamera();
};