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

	bool texture = false;

public:
	DrawableObject();
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation);
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, const char* textureName);
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, bool isSkybox);
	~DrawableObject();

	void setShader(ShaderProgram* shader);
	ShaderProgram* getShader();

	glm::mat4 getModelMatrix();
	void setTransformation(glm::mat4 matrix);
	Transformation* getTransformation();

	Model* getModel();
	GLuint getTextureID();

	void useShader();
	void Draw(Camera* cam);

	bool isTexture();

};