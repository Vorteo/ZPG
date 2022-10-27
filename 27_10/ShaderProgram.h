#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Headers.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderLoader.h"

class Camera;
class ShaderProgram : public ShaderLoader
{
private:
	GLuint Program;

public:
	ShaderProgram();
	ShaderProgram(const char* fragmentFile, const char* vertexFile);
	~ShaderProgram();

	void UseProgram();
	void CheckStatus();
	GLint getMatrix(const char* matrixName);

	void setMatrix(glm::mat4 matrix, const char* matrixName);
	void setVec3(glm::vec3 vectr, const char* vectorName);
};
#endif