#pragma once

#include "Headers.h"
#include "ShaderProgram.h"
#include "Model.h"

using namespace std;

class Application 
{
private:
	static Application* instance;
	Application();
	
	GLint status;
	GLFWwindow* window;

	ShaderProgram* shaderProgram;

	Model* model;

public:
	static Application* GetInstance();
	~Application();
	void AddModel(Model* model);

	void VersionInfo();
	void InitSpecificVersion();
	void CheckStatus();
	void Setup();
	void Run();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};