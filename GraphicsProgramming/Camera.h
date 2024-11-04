#pragma once
#include "glm.hpp"


class Camera
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	const glm::mat4& modelMatrix = _model;
	const glm::mat4& viewMatrix = _view;
	const glm::mat4& projectionMatrix = _projection;

	float nearPlane, farPlane;
	float fov;

	void Init();
	void Update();

	void Translate(float, float, float);

private:
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

};

