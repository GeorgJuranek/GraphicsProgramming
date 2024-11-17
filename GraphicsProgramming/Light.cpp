#pragma once
#include "Light.h"
#include "glm.hpp"
#include <gtc\matrix_transform.hpp>

void Light::Init()
{
	position = glm::vec3(0.0f, 0.0f, -1.0f);
	ambient = glm::vec3(0.3f, 0.3f, 0.0f);
	diffuse = glm::vec3(0.3f, 0.3f, 0.0f);
	specular = glm::vec3(0.3f, 0.3f, 0.0f);

	//attenuationConst = 1.0f;
	//attenuationLinear = 0.3f;
	//attenuationQuad = 0.1f;

}


void Light::Translate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
	_model = glm::translate(_model, glm::vec3(x, y, z));
}
