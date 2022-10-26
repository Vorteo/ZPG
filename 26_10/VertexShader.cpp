#include "VertexShader.h"

VertexShader::VertexShader()
{
	this->vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 in_Color;"

		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"

		"out vec3 color;"


		"void main () {"
		"     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);"
		"	  color = in_Color;"
		"}";

	//create and compile shaders
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(this->vertexShader);
}

VertexShader::VertexShader(const char* code)
{
	this->vertex_shader = code;

	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &this->vertex_shader, NULL);
	glCompileShader(this->vertexShader);
}

VertexShader::~VertexShader()
{
	delete this->vertex_shader;
}

GLuint VertexShader::GetVertex()
{
	return this->vertexShader;
}
