#pragma once

#include "Headers.h"

class Model
{
protected:
	const float *points;
	int size;

	GLuint VBO;
	GLuint VAO;

	glm::mat4 modelMatrix;

public:
	Model();
	Model(const float points[], int size);
	Model(const float points[], int size, bool isTexture);
	~Model();
	void drawModel();

	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);

};
