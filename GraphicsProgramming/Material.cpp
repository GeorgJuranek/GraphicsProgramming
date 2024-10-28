#include "Material.h"

Material::Material()
{
	ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
	shininess = 1.0f;
}
