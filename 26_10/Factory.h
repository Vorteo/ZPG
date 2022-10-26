#pragma once
#include "Headers.h"
#include "DrawableObject.h"
#include "Models/sphere.h"

class Factory
{
private:
	static Factory* instance;
	Factory();	
public:
	static Factory* GetInstance();
	~Factory();
	DrawableObject createObject(int shaderType);
};