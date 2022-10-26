#include "Model.h"

Model::Model()
{
	this->points = nullptr;
	this->size = -1;

	this->VAO = 0;
	this->VBO = 0;

	this->modelMatrix = glm::mat4(1.0f);
}

Model::Model(const float points[], int size)
{
	this->points = points;
	this->size = size;

	this->modelMatrix = glm::mat4(1.0f);

	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->points) * this->size, &this->points[0], GL_STATIC_DRAW);

	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3));

}

Model::~Model()
{
	delete[] this->points;
}

void Model::drawModel()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->size);
}

glm::mat4 Model::getModelMatrix()
{
	return this->modelMatrix;
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}


