#pragma once
#include "Headers.h"

class Observer
{
public:
	virtual void update(glm::mat4 matrixValue, const char* matrixName) = 0;
};
