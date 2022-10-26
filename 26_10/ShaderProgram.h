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

	GLuint getShaderProgram();
	void UseProgram();
	GLint getModelMatrix();
};
#endif