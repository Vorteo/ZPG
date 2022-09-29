#pragma once

#include "Headers.h"

class Model
{
private:
	float *points;
	int size;

	GLuint VBO;
	GLuint VAO;

public:
	Model();
	Model(float points[], int size);
	~Model();
	GLuint GetVAO();

};