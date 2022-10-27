#pragma once
#include "Headers.h"

class Observer
{
public:
	virtual void update(glm::mat4 matrixValue, glm::mat4 matrixName) = 0;
};

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void attach(Observer* o)
	{
		observers.push_back(o);
	}

	void dettach(Observer* o)
	{
		observers.erase(std::remove(observers.begin(),observers.end(), o), observers.end());
	}

	void notify()
	{
		for (int i = 0; i < observers.size(); i++)
		{
			//observers[i]->update();
		}
	}
};