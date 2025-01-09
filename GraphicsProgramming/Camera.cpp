#include "Camera.h"
#include <gtc\matrix_transform.hpp>
#include "Framework.h"
#include "Error.h"

void Camera::Init()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	//TEST
	//_rotation = glm::vec3(0.0f, 1.0f, 0.0f);

	_view = lookAt(position, position+direction, up);

	nearPlane = 0.1f;
	farPlane = 100.0f;
	fov = 45.0f;

	_projection = glm::perspective(fov, float(800) / 600, nearPlane, farPlane);

}

void Camera::Update()
{
	
}

void Camera::Translate(float x, float y, float z)
{
	glm::vec3 right = glm::normalize(glm::cross(direction, up)); //crossproduct always points to right-side
	glm::vec3 forward = glm::normalize(-direction);

	glm::vec3 movement = (right * x) + (up * y) + (forward * z); //apply values

	position += movement;

	_view = glm::lookAt(position, position + direction, up);
}



//void Camera::ChangeViewFromMouse(float mouseX, float mouseY)
//{
//	direction += glm::vec3(mouseX, -mouseY, -1.0f);
//	_view = lookAt(position, position + direction, up);
//}

void Camera::ChangeViewFromMouse(float mouseX, float mouseY) 
{
    //*Code partly from Inet

    float sensitivity = 0.1f; // tone sesnsitivity down
    mouseX *= sensitivity;
    mouseY *= sensitivity;

    //remember mouse values to check and use them later
    horizontal += mouseX;
    vertical -= mouseY;

    // vertical must be between -89° and 89° to stay correct, otherwise cam would "fall"
    if (vertical > 89.0f)
        vertical = 89.0f;
    if (vertical < -89.0f)
        vertical = -89.0f;

    //Some Magic from the internet, using cos, sin, tan
    glm::vec3 newDirection;
    newDirection.x = cos(glm::radians(horizontal)) * cos(glm::radians(vertical));
    newDirection.y = sin(glm::radians(vertical));
    newDirection.z = sin(glm::radians(horizontal)) * cos(glm::radians(vertical));
    direction = glm::normalize(newDirection);

    //Update
    _view = glm::lookAt(position, position + direction, up);
}
