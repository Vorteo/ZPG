#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Headers.h"
#include "Factory.h"
#include "Controller.h"

using namespace std;

class Controller;
class Application
{
private:
	static Application* instance;
	Application();
	
	GLFWwindow* window;
	Controller* controller;
	Scene* scene;

	int rightClick = 0;
public:
	static Application* getInstance();
	~Application();

	void versionInfo();
	void initSpecificVersion();
	void setup();
	void run();

	void setRightClick(int rightClick);
	int getRightClick();

	Factory* factory;

	void setScene(Scene* scene);
	Scene* getScene();

	Camera* getCamera();
};
#endif