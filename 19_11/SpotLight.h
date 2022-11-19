#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	glm::vec3 direction;
	float cutOff;

public:
	SpotLight(glm::vec3 direction, glm::vec3 position);
	~SpotLight();

	void setCutOff(float cutOff);
	void setDirection(glm::vec3 direction);
	
	float getCutOff();
	glm::vec3 getDirection();
};