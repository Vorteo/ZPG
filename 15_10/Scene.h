#pragma once

#include "Model.h"
#include "Camera.h"

#include<vector>

class Scene 
{
private:
	std::vector<Model*> models;
	Camera* camera;

public:
	Scene();
	~Scene();

	void addModel(Model* model);
	void drawScene(ShaderProgram* program);
	void setModelMatrixOfModel(glm::mat4 modelMatrix, int i);
};