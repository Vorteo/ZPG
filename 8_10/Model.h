#pragma once

#include "Headers.h"

class Model
{
private:
	float *points;
	int size;

	GLuint VBO;
	GLuint VAO;

	glm::mat4 modelMatrix;

public:
	Model();
	Model(float points[], int size);
	~Model();
	void drawModel();
	glm::mat4 getModelMatrix();

};