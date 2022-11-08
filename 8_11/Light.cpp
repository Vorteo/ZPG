#include "Light.h"

Light::Light()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Light::Light(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Light::getPosition()
{
	return this->position;
}

void Light::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

Light::~Light()
{

}
