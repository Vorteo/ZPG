#include "DrawableObject.h"

int countID = 1;

DrawableObject::DrawableObject()
{
	this->objectID = countID++;

	this->shader = nullptr;
	this->model = nullptr;
	this->transformation = nullptr;

	this->assimp = false;
	this->texture = false;
	this->skybox = false;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation)
{
	this->objectID = countID++;

	this->model = model;
	this->shader = shader;
	this->transformation = transformation;

	this->assimp = false;
	this->texture = false;
	this->skybox = false;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, const char* textureName)
{
	this->objectID = countID++;

	this->model = model;
	this->shader = shader;
	this->transformation = transformation;

	this->texture = true;
	this->assimp = false;
	this->skybox = false;

	this->textureID = SOIL_load_OGL_texture(textureName, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (this->textureID == NULL)
	{
		exit(EXIT_FAILURE);
	}
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, bool isSkybox)
{
	this->objectID = countID++;

	this->model = model;
	this->shader = shader;
	this->transformation = transformation;

	this->assimp = false;
	this->texture = false;
	this->skybox = isSkybox;

	this->textureID = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (this->textureID == NULL)
	{
		exit(EXIT_FAILURE);
	}
}

DrawableObject::DrawableObject(Model* model, bool isAssimp, ShaderProgram* shader, Transformation* transformation)
{
	this->objectID = countID++;

	this->model = model;
	this->shader = shader;
	this->transformation = transformation;
	this->textureID = -1;

	this->assimp = isAssimp;
	this->texture = false;
	this->skybox = false;
}

DrawableObject::~DrawableObject()
{
	this->objectID = -1;

	delete this->model;
	delete this->shader;
	delete this->transformation;
}

void DrawableObject::setShader(ShaderProgram* shader)
{
	this->shader = shader;
}

ShaderProgram* DrawableObject::getShader()
{
	return this->shader;
}

glm::mat4 DrawableObject::getModelMatrix()
{
	this->model->setModelMatrix(this->transformation->getTransformationMatrix());
	return this->model->getModelMatrix();
}

void DrawableObject::setTransformation(glm::mat4 matrix)
{
	this->transformation->setTransform(matrix);
}

Transformation* DrawableObject::getTransformation()
{
	return this->transformation;
}

Model* DrawableObject::getModel()
{
	return this->model;
}

GLuint DrawableObject::getTextureID()
{
	return this->textureID;
}

void DrawableObject::useShader()
{
	this->shader->UseProgram();
}

void DrawableObject::Draw(Camera* cam)
{
	// MODEL
	this->getShader()->setMatrix(this->getModelMatrix(), "modelMatrix");

	// VIEW
	this->getShader()->setMatrix(cam->getCamera(), "viewMatrix");

	// PROJECTION
	this->getShader()->setMatrix(cam->getProjectionMatrix(), "projectionMatrix");

	this->model->drawModel();
}

bool DrawableObject::isTexture()
{
	return this->texture;
}

bool DrawableObject::isAssimp()
{
	return this->assimp;
}

int DrawableObject::getID()
{
	return this->objectID;
}
