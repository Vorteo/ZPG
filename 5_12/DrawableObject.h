#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

class DrawableObject
{
private:
	int objectID;

	ShaderProgram* shader;
	Model* model;
	Transformation* transformation;

	GLuint textureID = NULL;

	bool texture;
	bool assimp;
	bool skybox;

public:
	DrawableObject();
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation);
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, const char* textureName);
	DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, bool isSkybox);
	DrawableObject(Model* model, bool isAssimp, ShaderProgram* shader, Transformation* transformation);
	~DrawableObject();

	void setShader(ShaderProgram* shader);
	ShaderProgram* getShader();

	glm::mat4 getModelMatrix();
	void setTransformation(glm::mat4 matrix);
	Transformation* getTransformation();

	Model* getModel();
	GLuint getTextureID();

	void activateShader();
	void deactivateShader();
	void draw(Camera* cam);

	bool isTexture();
	bool isAssimp();

	int getID();

};