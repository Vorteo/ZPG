#pragma once
#include "Headers.h"


class AssimpModel
{
private:
	int indicesCount;
	GLuint IBO;
public:
	AssimpModel();
	~AssimpModel();

	void Load(std::string fileName);
};