#include "Light.h"

Light::Light()
{
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);

}

Light::Light(glm::vec3 color)
{
	this->color = color;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

void Light::setColor(glm::vec3 color)
{
	this->color = color;
}

Light::~Light()
{

}
