#include "ShaderLoader.h"

string ShaderLoader::loadFile(const char* fname)
{
	ifstream file(fname);
	if (!file.is_open())
	{
		cout << "Unable to open file " << fname << endl;
		//exit(1);
	}
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

GLuint ShaderLoader::loadShader(const char* vertexFile, const char* fragmentFile) 
{
	printf("Shader::loadShader %s %s \n", vertexFile, fragmentFile);
	string vertexShaderString = loadFile(vertexFile);
	string fragmentShaderString = loadFile(fragmentFile);
	int vlen = vertexShaderString.length();
	int flen = fragmentShaderString.length();

	if (vertexShaderString.empty()) printf("Empty Vertex Shader\n");
	if (fragmentShaderString.empty()) printf("Empty Fragment Shader\n");

	const char* vertexShaderCStr = vertexShaderString.c_str();
	const char* fragmentShaderCStr = fragmentShaderString.c_str();

	this->vertex = new VertexShader(vertexShaderCStr);
	this->fragment = new FragmentShader(fragmentShaderCStr);

	return shaderProgramID;
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

ShaderLoader::ShaderLoader(const char* vertexFile, const char* fragmentFile, GLuint* shaderID) {

	*shaderID = loadShader(vertexFile, fragmentFile);
}

ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}
