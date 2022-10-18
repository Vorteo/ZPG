#pragma once

#include "Headers.h"

class FragmentShader
{
private:
	const char* fragment_shader;
	GLuint fragmentShader;
public:
	FragmentShader();
	FragmentShader(const char* code);
	~FragmentShader();
	GLuint GetFragment();
};