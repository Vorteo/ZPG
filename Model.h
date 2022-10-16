#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Headers.h"
#include "Transformation.h"

class Model : public Transformation
{
private:
	float *points;
	int size;

	GLuint VBO;
	GLuint VAO;

	// glm::mat4 modelMatrix;

public:
	Model();
	Model(float points[], int size);
	~Model();
	void drawModel();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);

};
#endif