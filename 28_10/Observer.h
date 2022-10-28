#pragma once
#include "Headers.h"

class Observer
{
public:
	virtual void update(glm::mat4 matrixValue, glm::mat4 matrixName) = 0;
};
