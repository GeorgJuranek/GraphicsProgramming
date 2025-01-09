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

	//TEST
	//void Rotate(float angle, glm::vec3 axis);
	void ChangeViewFromMouse(float mouseX, float mouseY);

	float horizontal = -90;
	float vertical;

private:
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

	//TEST
	//glm::vec3 _rotation;
};

