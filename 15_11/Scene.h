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

	ShaderProgram* constant, *lambert, *phong, *blinnPhong, *texture, *skybox, *lights;

	PointLight* pointLight;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;

public:
	Scene();
	~Scene();

	void addDrawableObject(DrawableObject* object,int shaderType);
	void drawScene(int width, int height);

	glm::vec3 getLightPosition();
	Camera* getCamera();

	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

};