#include "SkyBox.h"
#include "Models/skycube.h"

SkyBox::SkyBox()
{
    this->points = skycube;
    this->size = sizeof(skycube) / sizeof(skycube[0]);

    this->VBO = 0;
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->points) * this->size, &this->points[0], GL_STATIC_DRAW);

    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    this->modelMatrix = glm::mat4(1.0f);

}
