#include "ShaderLoader.h"

string ShaderLoader::loadFile(const char* fname)
{
	ifstream file(fname);
	if (!file.is_open())
	{
		cout << "Unable to open file" << fname << endl;
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

GLuint ShaderLoader::loadShader(const char* vertexFile, const char* fragmentFile)
{
	return 10;
}

void ShaderLoader::deleteShader()
{
	printf("ShaderLoader::deleteShader()\n");
	glDetachShader(shaderProgramID, vertexID);
	glDetachShader(shaderProgramID, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgramID);
}

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}