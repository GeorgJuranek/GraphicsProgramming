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

	void Init();

private:

	GLuint positionID, ambientID, diffuseID, specularID;
	void CreateBuffers();
};

