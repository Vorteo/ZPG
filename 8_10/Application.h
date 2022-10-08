#pragma once

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


public:
	static Application* GetInstance();
	~Application();
	void AddModel(Model* model);

	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
	void Setup();
	void Run();

};