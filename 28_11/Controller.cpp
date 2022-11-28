#include "Controller.h"

Controller* Controller::instance = 0;

Controller* Controller::GetInstance()
{
	if (!instance)
	{
		instance = new Controller();
	}

	return instance;
}

void Controller::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		printf("space \n");
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Application::GetInstance()->getScene()->getCamera()->toFront();
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Application::GetInstance()->getScene()->getCamera()->toBack();
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Application::GetInstance()->getScene()->getCamera()->toLeft();
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Application::GetInstance()->getScene()->getCamera()->toRight();
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	
	if (Application::GetInstance()->getRightClick() == 1)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Application::GetInstance()->getScene()->getCamera()->mouseMove(x,y,width, height);
	}

	printf("cursor_callback [%.1f,%.1f] \n", x, y);
	
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		Application::GetInstance()->setRightClick(1);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		Application::GetInstance()->setRightClick(0);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		double cur_x, cur_y;
		glfwGetCursorPos(window, &cur_x, &cur_y);

		GLint x = (GLint)cur_x;
		GLint y = (GLint)cur_y;

		int w, h;
		glfwGetWindowSize(window, &w, &h);

		int new_y = h - y;

		glReadPixels(x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, new_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
		
		glm::vec3 screenX = glm::vec3(x, new_y, depth);
		glm::mat4 view = Application::GetInstance()->getCamera()->getCamera();
		glm::mat4 projection = Application::GetInstance()->getCamera()->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, w, h);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		Application::GetInstance()->factory->addTreeOnPosition(Application::GetInstance()->getScene(), pos);
	}

	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

}
