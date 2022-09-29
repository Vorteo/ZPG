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
	this->shaderProgram = new ShaderProgram();
	this->model = new Model();
}

Application::~Application()
{
	delete this->shaderProgram;
}

void Application::AddModel(Model* model)
{
	this->model = model;
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::CheckStatus()
{
	glGetProgramiv(this->shaderProgram->getShaderProgram(), GL_LINK_STATUS, &this->status);
	if (this->status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram->getShaderProgram(), GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram->getShaderProgram(), infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Application::Setup()
{
	glfwSetErrorCallback(this->error_callback);

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
	glfwSetKeyCallback(this->window, this->key_callback);
	glfwSetCursorPosCallback(this->window, this->cursor_callback);
	glfwSetMouseButtonCallback(this->window, this->button_callback);
	glfwSetWindowFocusCallback(this->window, this->window_focus_callback);
	glfwSetWindowIconifyCallback(this->window, this->window_iconify_callback);
	glfwSetWindowSizeCallback(this->window, this->window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	this->VersionInfo();
}

void Application::Run()
{
	while (!glfwWindowShouldClose(this->window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->shaderProgram->UseProgram();
		glBindVertexArray(this->model->GetVAO());
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 6); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//*******************************************************
//**** Callback methods ****
void Application::error_callback(int error, const char* description)
{
	 fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		printf("space \n");
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}

