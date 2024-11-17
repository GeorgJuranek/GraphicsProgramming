#include "Camera.h"
#include <gtc\matrix_transform.hpp>
#include "Framework.h"
#include "Error.h"

void Camera::Init()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	_view = lookAt(position, position+direction, up);

	nearPlane = 0.1f;
	farPlane = 100.0f;
	fov = 45.0f;

	_projection = glm::perspective(fov, float(800) / 600, nearPlane, farPlane);
	//_projection = glm::perspective(glm::radians(fov), float(800) / 600, nearPlane, farPlane);

	//Test
	//_model = glm::mat4(1.0);
}

void Camera::Update()
{
	//if (Framework::)
}

void Camera::Translate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
	_model = glm::translate(_model, glm::vec3(x, y, z));
}
