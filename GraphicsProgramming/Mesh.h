#pragma once
#include <array>
#include <GL\glew.h>
#include "Material.h"
#include "Shader.h"
#include "Buffer.h"
#include "Light.h"

class Mesh
{
public:
	std::array<GLfloat, 4 * 3> vertexPositions;
	std::array<GLfloat, 4 * 3> vertexColors;
	std::array<GLuint, 6> indices;

	Material* material = nullptr;
	Shader* shader = nullptr;

	void Init(Shader* shader, Material* material);
	void GetLightUniformIDs();
	void GetMaterialUniformIDs();

	void Draw(Light light);
	void Release();

private:
	Buffer positionBuffer, colorBuffer, indexBuffer;
	GLuint vao;
	GLuint lightPositionID, lightAmbientID, lightDiffuseID, lightSpecularID;

	GLuint materialAmbientID, materialDiffuseID, materialSpecularID, materialShininessID; //?

	void CreateBuffers();

};

