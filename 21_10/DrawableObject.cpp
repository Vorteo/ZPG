#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, Transformation* transformation)
{
	this->model = model;
	this->shader = shaderProgram;
	this->transformation = transformation;
}

DrawableObject::~DrawableObject()
{
	delete this->model;
	delete this->shader;
	delete this->transformation;
}

void DrawableObject::setShader(ShaderProgram* shaderProgram)
{
	this->shader = shaderProgram;
}
