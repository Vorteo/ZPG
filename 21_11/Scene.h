#pragma once

#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "DrawableObjectManager.h"

#include<vector>



class Scene 
{
private:
	//DrawableObjectManager* manager;
	std::vector<DrawableObject*> objects;
	DrawableObject* skyboxObject = nullptr;
	Camera* camera;

	ShaderProgram* constant, *lambert, *phong, *blinnPhong, *texture, *skybox, *lights;

	PointLight* pointLight;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;


	bool first = true;
public:
	Scene();
	~Scene();

	void addDrawableObject(DrawableObject* object,int shaderType);
	void setSkybox(DrawableObject* object);
	void drawScene(int width, int height);
	void drawSkyBox();

	glm::vec3 getLightPosition();
	Camera* getCamera();

	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

};