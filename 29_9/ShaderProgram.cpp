#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->vertex = new VertexShader();
	this->fragment = new FragmentShader();

	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->fragment->GetFragment());
	glAttachShader(this->Program, this->vertex->GetVertex());
	glLinkProgram(this->Program);
}

void ShaderProgram::UseProgram()
{
	glUseProgram(this->Program);
}

GLuint ShaderProgram::getShaderProgram()
{
	return this->Program;
}

ShaderProgram::~ShaderProgram()
{

}

