#include "SpotLight.h"

SpotLight::SpotLight()
{
	this->direction = glm::vec3(0.0f, -1.0f, 0.0f);
	this->cutOff = glm::cos(glm::radians(12.5f));
}

SpotLight::SpotLight(glm::vec3 color, glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 direction, float angle) : PointLight(color,position, constant, linear, quadratic)
{
	this->direction = direction;
	this->cutOff = glm::cos(glm::radians(angle));
}

void SpotLight::setCutOff(float cutOff)
{
	this->cutOff = glm::cos(glm::radians(cutOff));
}

void SpotLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

float SpotLight::getCutOff()
{
	return this->cutOff;
}

glm::vec3 SpotLight::getDirection()
{
	return this->direction;
}

SpotLight::~SpotLight()
{

}
