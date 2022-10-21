#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "Headers.h"

class Model
{
private:
	const float *points;
	int size;

	GLuint VBO;
	GLuint VAO;

	glm::mat4 modelMatrix;

public:
	Model();
	Model(const float points[], int size);
	~Model();
	void drawModel();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);

};
#endif