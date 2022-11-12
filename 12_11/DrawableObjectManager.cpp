#include "DrawableObjectManager.h"

DrawableObjectManager::DrawableObjectManager()
{
	this->objects =  std::vector<DrawableObject*>();
}

void DrawableObjectManager::addDrawableObject(DrawableObject* object)
{

	this->objects.push_back(object);

}

void DrawableObjectManager::removeDrawableObject(int index)
{
	this->objects.erase(this->objects.begin() + index);
}

DrawableObject* DrawableObjectManager::getDrawableObjectOnIndex(int index)
{
	if (index < 0 || index >= this->objects.size())
	{
		exit(EXIT_FAILURE);
	}
	return this->objects[index];
}

int DrawableObjectManager::getNumberOfDrawableObjects()
{
	return ((int)this->objects.size());
}

DrawableObjectManager::~DrawableObjectManager()
{
	this->objects.clear();
}
