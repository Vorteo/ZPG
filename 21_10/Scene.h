#pragma once

#include "Model.h"
#include "Camera.h"
#include "Light.h"
//#include "DrawableObject.h"

#include<vector>

class Scene 
{
private:
	std::vector<Model*> models;
	//std::vector<DrawableObject*> objects;
	Camera* camera;
	Light* light;

public:
	Scene();
	~Scene();

	void addModel(Model* model);
	//void addDrawableObject(DrawableObject* object);
	void drawScene(ShaderProgram* program);
	void setModelMatrixOfModel(glm::mat4 modelMatrix, int i);
	glm::vec3 getLightPosition();
};