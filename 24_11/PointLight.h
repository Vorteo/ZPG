#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

public:
	PointLight();
	PointLight(glm::vec3 color, glm::vec3 position, float constant, float linear, float quadratic);
	~PointLight();

	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	float getConstant();
	float getLinear();
	float getQuadratic();

};
