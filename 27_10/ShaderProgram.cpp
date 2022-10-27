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

ShaderProgram::ShaderProgram(const char* fragmentFile, const char* vertexFile)
{
	this->loadShader(vertexFile, fragmentFile);

	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->fragment->GetFragment());
	glAttachShader(this->Program, this->vertex->GetVertex());
	glLinkProgram(this->Program);
	this->CheckStatus();
}

void ShaderProgram::UseProgram()
{
	glUseProgram(this->Program);
}

void ShaderProgram::CheckStatus()
{
	GLint status;

	glGetProgramiv(this->Program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->Program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->Program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

GLint ShaderProgram::getMatrix(const char* matrixName)
{
	GLint idModelTransform = glGetUniformLocation(this->Program, matrixName);

	if (idModelTransform != -1)
	{
		return idModelTransform;
	}

	return idModelTransform;
}

void ShaderProgram::setMatrix(glm::mat4 matrix, const char* matrixName)
{
	glUniformMatrix4fv(glGetUniformLocation(this->Program, matrixName), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setVec3(glm::vec3 vectr, const char* vectorName)
{
	glUniform3fv(glGetUniformLocation(this->Program, vectorName), 1, glm::value_ptr(vectr));
}

ShaderProgram::~ShaderProgram()
{
	delete this->vertex;
	delete this->fragment;
}

