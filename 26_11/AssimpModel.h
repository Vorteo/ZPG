#pragma once
#include "Model.h"


class AssimpModel : public Model
{
private:
	int indicesCount;
	GLuint IBO;

	GLuint textureID;
	GLuint textureUnitID;
	

public:
	AssimpModel();
	~AssimpModel();

	void load(std::string fileName);
	void loadTexture(const char* textureName);

	int getIndices();
	GLuint getTextureID();
	GLuint getTextureUnit();

	void bindIBO();
	void unbindIBO();
	
};