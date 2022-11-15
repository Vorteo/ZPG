#include "PointLight.h"

PointLight::PointLight()
{
	this->constant = 1.0;
	this->linear = 0.1;
	this->quadratic = 0.01;
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic) : Light(position)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
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
