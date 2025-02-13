#pragma once
#include <array>
#include <GL\glew.h>
#include "Material.h"
#include "Shader.h"
#include "Buffer.h"
#include "Light.h"
#include "MeshLoader.h"

#include "Camera.h"
#include <vector>


#include <assimp/scene.h> 
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Mesh
{
public:
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> uvCoordinates;
	std::vector<GLfloat> vertexNormals;
	std::vector<GLuint> indices;

	std::vector<GLuint> uvIndices;
	std::vector<GLuint> normalIndices;

	Material* material = nullptr;
	Shader* shader = nullptr;

	void Init(Shader* shader, Material* material, string meshFilePath);
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

	glm::vec3 GetRotation(void);

	void LoadFromMeshData(MeshData* mesh);

private:
	Buffer positionBuffer, uvBuffer, indexBuffer, colorBuffer, normalBuffer;
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
	glm::mat4 _mvp;


};

