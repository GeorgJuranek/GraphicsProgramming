#include "Light.h"

void Light::Init()
{
	position = glm::vec3(0.0f, 0.0f, -1.0f);
	ambient = glm::vec3(0.3f, 0.3f, 0.0f);
	diffuse = glm::vec3(0.3f, 0.3f, 0.0f);
	specular = glm::vec3(0.3f, 0.3f, 0.0f);
}

void Light::CreateBuffers()
{
}
