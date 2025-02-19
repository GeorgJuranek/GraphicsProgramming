#pragma once
#include "glm.hpp"

class Material
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material();
};

