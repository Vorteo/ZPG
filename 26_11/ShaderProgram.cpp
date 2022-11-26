#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->vertex = new VertexShader();
	this->fragment = new FragmentShader();

	this->observedCamera = nullptr;

	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->fragment->GetFragment());
	glAttachShader(this->Program, this->vertex->GetVertex());
	glLinkProgram(this->Program);
}

ShaderProgram::ShaderProgram(const char* fragmentFile, const char* vertexFile)
{
	this->loadShader(vertexFile, fragmentFile);

	this->observedCamera = nullptr;

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

void ShaderProgram::DeactivateProgram()
{
	glUseProgram(0);
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

void ShaderProgram::setFloat(float value, const char* variableName)
{

	glUniform1f(glGetUniformLocation(this->Program, variableName), value);
}

void ShaderProgram::setInt(int value, const char* variableName)
{
	glUniform1i(glGetUniformLocation(this->Program, variableName), value);
}

void ShaderProgram::bindTexture(GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	this->setInt(0, "textureUnitID");

}

void ShaderProgram::bindSkyBox(GLuint textureID)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	this->setInt(0, "textureUnitID");
}

void ShaderProgram::update(glm::mat4 matrixValue, const char* matrixName)
{
	this->setMatrix(matrixValue, matrixName);
}

void ShaderProgram::setObservedCamera(Camera* c)
{
	this->observedCamera = c;
	if (!c->findShader(this))
	{
		c->attachShader(this);
		c->update();
	}
	else
	{
		c->update();
	}
}


ShaderProgram::~ShaderProgram()
{
	delete this->vertex;
	delete this->fragment;
	delete this->observedCamera;
}

