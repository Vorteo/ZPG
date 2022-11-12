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

	GLuint textureID = NULL;

public:
	DrawableObject();
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation);
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, const char* textureName);
	~DrawableObject();

	void setShader(ShaderProgram* shader);
	ShaderProgram* getShader();

	glm::mat4 getModelMatrix();

	Model* getModel();
	GLuint getTextureID();

	void useShader();
	void Draw();

};