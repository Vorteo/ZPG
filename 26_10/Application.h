#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Headers.h"
#include "Controller.h"
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"

using namespace std;

class Controller;
class Application
{
private:
	static Application* instance;
	Application();

	GLint status;
	GLFWwindow* window;

	Controller* controller;
	ShaderProgram* shaderProgram;
	Scene* scene;

	Camera* camera;
	int rightClick = 0;


public:
	static Application* GetInstance();
	~Application();
	void AddModel(Model* model);

	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
	void Setup();
	void Run();

	Camera* getCamera();

	void setRightClick(int rightClick);
	int getRightClick();

};
#endif