#include "Model.h"

Model::Model()
{
	this->points = nullptr;
	this->size = -1;

	this->VAO = 0;
	this->VBO = 0;
}

Model::Model(float points[],int size)
{

	this->points = points;
	this->size = size;

	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->points) * this->size, this->points, GL_STATIC_DRAW);

	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(points), (GLvoid*)(3 * sizeof(float)));
}

Model::~Model()
{
	delete[] this->points;
}

GLuint Model::GetVAO()
{
	return this->VAO;
}
