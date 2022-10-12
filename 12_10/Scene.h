#pragma once
#ifndef SCENE_H
#define SCENE_H

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
};
#endif