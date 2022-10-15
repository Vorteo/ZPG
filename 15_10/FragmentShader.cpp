#include "FragmentShader.h"

FragmentShader::FragmentShader()
{
	this->fragment_shader = 
			"#version 330\n"
			"out vec4 frag_colour;"
			"in vec3 color;"
			"void main () {"
			"     frag_colour = vec4 (color, 1.0);"
			"}";

	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &this->fragment_shader, NULL);
	glCompileShader(this->fragmentShader);
}

FragmentShader::FragmentShader(const char* code)
{
	this->fragment_shader = code;
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &this->fragment_shader, NULL);
	glCompileShader(this->fragmentShader);
}

FragmentShader::~FragmentShader()
{
	delete this->fragment_shader;
}

GLuint FragmentShader::GetFragment()
{
	return this->fragmentShader;
}
