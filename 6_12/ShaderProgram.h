#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Headers.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Observer.h"

class Camera;
class ShaderProgram : public Observer, public ShaderLoader
{
private:
	GLuint Program;
	Camera* observedCamera;

public:
	ShaderProgram();
	ShaderProgram(const char* fragmentFile, const char* vertexFile);
	~ShaderProgram();

	void activateProgram();
	void deactivateProgram();

	void checkStatus();
	GLint getMatrix(const char* matrixName);

	void setMatrix(glm::mat4 matrix, const char* matrixName);
	void setVec3(glm::vec3 vectr, const char* vectorName);
	void setFloat(float value, const char* variableName);
	void setInt(int value, const char* variableName);

	void bindTexture(GLuint textureID);
	void bindSkyBox(GLuint textureID);
	
	void update(glm::mat4 matrixValue, const char* matrixName);
	void setObservedCamera(Camera* c);
};
#endif