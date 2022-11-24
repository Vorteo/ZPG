#pragma once

#include "DrawableObject.h"

class DrawableObjectManager
{
private:
	std::vector<DrawableObject*> objects;

public:
	DrawableObjectManager();
	~DrawableObjectManager();

	void addDrawableObject(DrawableObject* object);
	void removeDrawableObject(int index);

	DrawableObject* getDrawableObjectByIndex(int position);
	int getSize();
};
