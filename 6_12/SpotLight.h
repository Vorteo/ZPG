#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
	glm::vec3 direction;
	float cutOff;
	float OuterCutOff;

public:
	SpotLight();
	SpotLight(glm::vec3 color, glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 direction, float angle, float outerAngle);
	~SpotLight();

	void setCutOff(float cutOff);
	void setDirection(glm::vec3 direction);
	
	float getCutOff();
	float getOuterCutOff();
	glm::vec3 getDirection();
};