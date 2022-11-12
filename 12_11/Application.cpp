#include "Application.h"

Application* Application::instance = 0;

Application* Application::GetInstance()
{
	if (!instance)
	{
		instance = new Application();
	}

	return instance;
}

Application::Application()
{
	this->Setup();
	this->factory = this->factory->GetInstance();
	this->controller = this->controller->GetInstance();
	this->scene = nullptr;
}

Application::~Application()
{
	delete this->controller;
	delete this->scene;
	delete this->factory;
}

void Application::VersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

}

void Application::InitSpecificVersion()
{
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/
}

void Application::Setup()
{
	glfwSetErrorCallback(this->controller->error_callback);

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// Sets the key callback
	glfwSetKeyCallback(this->window, this->controller->key_callback);
	glfwSetCursorPosCallback(this->window, this->controller->cursor_callback);
	glfwSetMouseButtonCallback(this->window, this->controller->button_callback);
	glfwSetWindowFocusCallback(this->window, this->controller->window_focus_callback);
	glfwSetWindowIconifyCallback(this->window, this->controller->window_iconify_callback);
	glfwSetWindowSizeCallback(this->window, this->controller->window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	this->VersionInfo();
}

void Application::Run()
{
	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(this->window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		
		//DRAW
		this->scene->drawScene(width, height);

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::setRightClick(int rightClick)
{
	this->rightClick = rightClick;
}

int Application::getRightClick()
{
	return (this->rightClick);
}

void Application::setScene(Scene* scene)
{
	this->scene = scene;
}

Scene* Application::getScene()
{
	return this->scene;
}

