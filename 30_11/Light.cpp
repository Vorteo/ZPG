#include "Light.h"

Light::Light()
{
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->type = 0;
}

Light::Light(glm::vec3 color)
{
	this->color = color;
	this->type = 0;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

int Light::getType()
{
	return this->type;
}

void Light::setColor(glm::vec3 color)
{
	this->color = color;
}

Light::~Light()
{

}
