#pragma once

#include "glm.hpp"
#include "GL\glew.h"

class Light
{
public:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	//float attenuationConst;
	//float attenuationLinear;
	//float attenuationQuad;

	void Init();
	void Translate(float x, float y, float z);

private:

	GLuint positionID, ambientID, diffuseID, specularID;

	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;
};

