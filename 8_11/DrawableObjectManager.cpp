#include "DrawableObjectManager.h"

DrawableObjectManager::DrawableObjectManager()
{
	this->objects =  std::vector<DrawableObject*>();
}

void DrawableObjectManager::addDrawableObject(DrawableObject* object)
{
	this->objects.push_back(object);
}

DrawableObject* DrawableObjectManager::getDrawableObjectOnIndex(int index)
{
	return this->objects[index];
}

DrawableObjectManager::~DrawableObjectManager()
{
	this->objects.clear();
}
