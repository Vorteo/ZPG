#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation)
{
	this->model = model;
	this->shader = shader;
	this->transformation = transformation;
}

DrawableObject::~DrawableObject()
{
	delete this->model;
	delete this->shader;
	delete this->transformation;
}

void DrawableObject::setShader(ShaderProgram* shader)
{
	this->shader = shader;
}
