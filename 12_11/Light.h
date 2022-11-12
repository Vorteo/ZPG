#pragma once
#include "Headers.h"

class Light 
{
private:
	glm::vec3 position;

public:
	Light();
	Light(glm::vec3 position);
	~Light();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
};