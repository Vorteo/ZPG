#pragma once
#include "Light.h"

class DirectionalLight
{
private:
	glm::vec3 direction;

public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction);
	~DirectionalLight();

	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
};