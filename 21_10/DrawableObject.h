#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

class DrawableObject
{
private:
	ShaderProgram* shader;
	Model* model;
	Transformation* transformation;

public:
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation);
	~DrawableObject();

	void setShader(ShaderProgram* shader);
};