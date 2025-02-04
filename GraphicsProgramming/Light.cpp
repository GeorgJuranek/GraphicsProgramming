#pragma once
#include "Light.h"
#include "glm.hpp"
#include <gtc\matrix_transform.hpp>

void Light::Init()
{
	position = glm::vec3(0.0f, 1.0f, 2.0f);
	ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);

	attenuationConst = 0.05f;
	attenuationLinear = 0.05f;
	attenuationQuad = 0.05f;

}


void Light::Translate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
	_model = glm::translate(_model, glm::vec3(x, y, z));
}
