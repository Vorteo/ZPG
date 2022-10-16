#pragma once
#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "Headers.h"

class VertexShader
{
private:
	const char* vertex_shader;
	GLuint vertexShader;

public:
	VertexShader();
	VertexShader(const char* code);
	~VertexShader();
	GLuint GetVertex();
};
#endif