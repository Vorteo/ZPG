#pragma once
#include "Model.h"
#include "ShaderProgram.h"

#include<vector>

class Scene 
{
private:
	std::vector<Model*> models;

public:
	Scene();
	~Scene();
	void addModel(Model* model);
	void drawScene(ShaderProgram* program);
};