#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 direction, glm::vec3 position) : Light(position)
{
	this->direction = direction;
	this->cutOff = glm::cos(glm::radians(12.5f));
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
