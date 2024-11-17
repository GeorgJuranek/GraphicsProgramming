#pragma once
#include <array>
#include <GL\glew.h>
#include "Material.h"
#include "Shader.h"
#include "Buffer.h"
#include "Light.h"

#include "Camera.h"
#include <vector>

class Mesh
{
public:
	//std::array<GLfloat, 4 * 3> vertexPositions;
	//std::array<GLfloat, 4 * 3> vertexColors;
	//std::array<GLfloat, 4 * 3> vertexNormals;
	//std::array<GLuint, 6> indices;
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> vertexColors;
	std::vector<GLfloat> vertexNormals;
	std::vector<GLuint> indices;

	Material* material = nullptr;
	Shader* shader = nullptr;

	void Init(Shader* shader, Material* material);
	void GetLightUniformIDs();
	void GetMaterialUniformIDs();

	void GetMVPUniformIDs();

	void Update();
	void Draw(Light* light);
	void Draw(Light* light, Camera* camera);
	void Release();

	void Translate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float angle, glm::vec3 axis);

	void SetPosition(glm::vec3 position);
	void SetPosition(float x, float y, float z);

private:
	Buffer positionBuffer, colorBuffer, indexBuffer;
	GLuint vao;
	GLuint lightPositionID, lightAmbientID, lightDiffuseID, lightSpecularID;

	GLuint materialAmbientID, materialDiffuseID, materialSpecularID, materialShininessID; //? 
	GLuint cameraPositionID;
	GLuint lightAttenuationConstID,lightAttenuationLinearID,lightAttenuationQuadID;

	GLuint modelID, mvpID, normalID;

	glm::vec3 position;

	Camera* camera;
	Light* light;

	void CreateBuffers();

	glm::vec3 _position;
	glm::vec3 _scale;
	glm::vec3 _rotation;
	glm::mat4 _model;
	glm::mat3 _normal;
	glm::mat4 _mvp;//glm::vec4 _mvp;


};

