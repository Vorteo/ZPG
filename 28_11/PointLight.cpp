#include "PointLight.h"

PointLight::PointLight()
{
	this->constant = 1.0;
	this->linear = 0.1;
	this->quadratic = 0.01;

	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->type = 1;
}

PointLight::PointLight(glm::vec3 color, glm::vec3 position, float constant, float linear, float quadratic) : Light(color)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;

	this->position = position;
	this->type = 1;
}

void PointLight::setConstant(float constant)
{
	this->constant = constant;
}

void PointLight::setLinear(float linear)
{
	this->linear = linear;
}

void PointLight::setQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}

void PointLight::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 PointLight::getPosition()
{
	return this->position;
}

float PointLight::getConstant()
{
	return this->constant;
}

float PointLight::getLinear()
{
	return this->linear;
}

float PointLight::getQuadratic()
{
	return this->quadratic;
}

PointLight::~PointLight()
{

}
