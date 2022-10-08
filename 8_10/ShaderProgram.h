#pragma once

#include "Headers.h"
#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram {
private:
	GLuint Program;

public:
	ShaderProgram();
	~ShaderProgram();
	GLuint getShaderProgram();
	void UseProgram();
	GLint getModelMatrix();

protected:
	VertexShader* vertex;
	FragmentShader* fragment;
};