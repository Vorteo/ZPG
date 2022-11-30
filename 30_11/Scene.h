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
	DrawableObject* skyboxObject = nullptr;
	Camera* camera;

	ShaderProgram* constant, *lambert, *phong, *blinnPhong, *texture, *skybox, *lights, *assimp;

	PointLight* pointLight;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;
	
public:
	Scene();
	~Scene();

	void addDrawableObject(DrawableObject* object,int shaderType);
	void setSkybox(DrawableObject* object);

	void drawScene(int width, int height);
	void drawSkyBox();
	void drawTextureObject(DrawableObject* obj);
	void drawAssimpObject(DrawableObject* obj);

	void sendLights(DrawableObject* obj);

	Camera* getCamera();
	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

};