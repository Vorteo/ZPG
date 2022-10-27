#pragma once
#include "Headers.h"

class Light 
{
private:
	glm::vec3 position;
public:
	Light();
	Light(glm::vec3 position);

	glm::vec3 getPosition();
};