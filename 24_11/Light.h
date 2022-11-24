#pragma once
#include "Headers.h"

class Light 
{
private:
	glm::vec3 color;

public:
	Light();
	Light(glm::vec3 color);
	~Light();

	glm::vec3 getColor();
	void setColor(glm::vec3 color);
};