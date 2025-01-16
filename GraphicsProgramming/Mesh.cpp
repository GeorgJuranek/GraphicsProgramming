#include "Mesh.h"
#include <gtc\matrix_transform.hpp>
#include "VertexLoader.h"

void Mesh::Init(Shader* shader, Material* material, string meshFilePath)
{
	MeshLoader* loader = MeshLoader::getInstance();
	MeshData* mesh = loader->loadFromFile(meshFilePath);//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/basicCube.obj");//C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/Pistol_02.obj");//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/CustomCube.obj");//

	LoadFromMeshData(mesh);

	this->shader = shader;
	this->material = material;

	CreateBuffers();
	GetLightUniformIDs();
	GetMaterialUniformIDs();
	GetMVPUniformIDs();
	cameraPositionID = shader->GetUniformLocation("cameraPosition");

	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_model = glm::mat4(1.0);

}

void Mesh::Draw(Light* light, Camera* camera)
{
	glUseProgram(shader->programID);

	glUniform3fv(lightPositionID, 1, &(light->position.x));
	glUniform3fv(lightAmbientID, 1, &(light->ambient.x));
	glUniform3fv(lightDiffuseID, 1, &(light->diffuse.x));
	glUniform3fv(lightSpecularID, 1, &(light->specular.x));

	//glUniform1f(lightAttenuationConstID, light->attenuationConst);
	//glUniform1f(lightAttenuationLinearID, light->attenuationLinear);
	//glUniform1f(lightAttenuationQuadID, light->attenuationQuad);

	glUniform3fv(materialAmbientID, 1, &(material->ambient.x));
	glUniform3fv(materialDiffuseID, 1, &(material->diffuse.x));
	glUniform3fv(materialSpecularID, 1, &(material->specular.x));
	glUniform1f(materialShininessID, material->shininess);

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &(_model[0][0]));

	_mvp = camera->projectionMatrix * camera->viewMatrix * _model;

	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &(_mvp[0][0]));

	_normal = glm::transpose(glm::inverse(_model));
	glUniformMatrix3fv(normalID, 1, GL_TRUE, &(_normal[0][0]));

	glUniform3fv(cameraPositionID, 1, &(camera->position.x));



	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::Release()
{
	positionBuffer.Delete();
	uvBuffer.Delete();
	indexBuffer.Delete();
}

void Mesh::CreateBuffers()
{
	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	//BUFFER: positionbuffer
	positionBuffer = {};

	const GLchar* attributeName = "positionIn";
	GLuint attributeID = shader->GetAttributeLocation(attributeName);
	positionBuffer.SetAttributeId(attributeID);
	positionBuffer.CreateBufferObject();
	positionBuffer.Bind(GL_ARRAY_BUFFER);
	positionBuffer.Fill(vertexPositions.size() * sizeof(GLfloat), &vertexPositions[0], GL_STATIC_DRAW);
	positionBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0);
	positionBuffer.EnableAttribute();

	//colorBuffer = {};
	//const GLchar* attributeColorName = "colorIn";
	//GLuint attributeColorID = shader->GetAttributeLocation(attributeColorName);
	//colorBuffer.SetAttributeId(attributeColorID);
	//colorBuffer.CreateBufferObject();
	//colorBuffer.Bind(GL_ARRAY_BUFFER);
	//colorBuffer.Fill(color.size() * sizeof(GLfloat), &vertexPositions[0], GL_STATIC_DRAW);
	//colorBuffer.LinkAttribute(4, GL_FLOAT, GL_FALSE, 0, 0); //reinterpret cast: to binary and back
	//colorBuffer.EnableAttribute();

	//UV BUFFER//
	uvBuffer = {};
	GLuint uvAttributeID = shader->GetAttributeLocation("uvIn");
	uvBuffer.SetAttributeId(uvAttributeID);
	uvBuffer.CreateBufferObject();
	uvBuffer.Bind(GL_ARRAY_BUFFER);
	uvBuffer.Fill(uvCoordinates.size() * sizeof(GLfloat), &uvCoordinates[0], GL_STATIC_DRAW);
	uvBuffer.LinkAttribute(2, GL_FLOAT, GL_FALSE, 0,0);
	uvBuffer.EnableAttribute();

	normalBuffer = {};
	const GLchar* attributeNormalName = "normalIn";
	GLuint attributeNormalID = shader->GetAttributeLocation(attributeNormalName);
	normalBuffer.SetAttributeId(attributeNormalID);
	normalBuffer.CreateBufferObject();
	normalBuffer.Bind(GL_ARRAY_BUFFER);
	normalBuffer.Fill(vertexNormals.size() * sizeof(GLfloat), &vertexNormals[0], GL_STATIC_DRAW);
	normalBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0); //reinterpret cast: to binary and back
	normalBuffer.EnableAttribute();

	//BUFFER: indexbuffer
	//indexBuffer = {};
	//indexBuffer.CreateBufferObject();
	//indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	//indexBuffer.Fill(indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);

	indexBuffer = {};
	indexBuffer.CreateBufferObject();
	indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.Fill(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	/*indexbuffer doesnt need to LinkAttribute and EnableAttribute 
	because its only for the sequence of indices*/


	//Job is done! Empty the vao
	glBindVertexArray(0);
}




void Mesh::GetLightUniformIDs()
{
	lightPositionID = shader->GetUniformLocation("light.position");
	lightAmbientID = shader->GetUniformLocation("light.ambient");
	lightDiffuseID = shader->GetUniformLocation("light.diffuse");
	lightSpecularID = shader->GetUniformLocation("light.specular");
}

void Mesh::GetMaterialUniformIDs()
{
	materialAmbientID = shader->GetUniformLocation("material.ambient");
	materialDiffuseID = shader->GetUniformLocation("material.diffuse");
	materialSpecularID = shader->GetUniformLocation("material.specular");
	materialShininessID = shader->GetUniformLocation("material.shininess");
}

void Mesh::GetMVPUniformIDs()
{
	modelID = shader->GetUniformLocation("model");
 
	mvpID = shader->GetUniformLocation("mvp");
	normalID = shader->GetUniformLocation("normal");
}


void Mesh::Update()
{
	Rotate(0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Mesh::Translate(float x, float y, float z)
{
	_position += glm::vec3(x, y, z);
	_model = glm::translate(_model, glm::vec3(x, y, z));
}

void Mesh::Scale(float x, float y, float z)
{
	_scale = glm::vec3(x, y, z);
	_model = glm::scale(_model, glm::vec3(x, y, z));
}

void Mesh::Rotate(float angle, glm::vec3 axis)
{
	_rotation += axis * angle;
	_model = glm::rotate(_model, glm::radians(angle), axis);

}

void Mesh::SetPosition(glm::vec3 position)
{
	SetPosition(position.x, position.y, position.z);
}

void Mesh::SetPosition(float x, float y, float z)
{
	glm::vec3 oldPos = position;
	_position = glm::vec3(x, y, z);
	_model = glm::translate(_model, position - oldPos);
}

glm::vec3 Mesh::GetRotation(void)
{
	return _rotation;
}

void Mesh::LoadFromMeshData(MeshData* mesh) {
	if (!mesh) {
		std::cerr << "No MashData passed to LoadFromMeshData!" << std::endl;
		return;
	}

	// Vertices
	vertexPositions.clear();
	if (mesh == nullptr || mesh->vertexCount == 0) {
		std::cerr << "Mesh has no vertices!" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < mesh->vertexPositions->size(); i++) {
		vertexPositions.push_back(mesh->vertexPositions->at(i));
	}

	vertexNormals.clear();
	if (mesh->normals->size() > 0) {
		for (unsigned int i = 0; i < mesh->normals->size(); i++) {
			vertexNormals.push_back(mesh->normals->at(i));
		}
	}
	else {
		std::cerr << "Mesh has no normals!" << std::endl;
		for (unsigned int i = 0; i < mesh->normals->size(); i++) {
			vertexNormals.push_back(0.0f);
		}
	}

	// Indices
	indices.clear();
	if (mesh->faceCount == 0) {
		std::cerr << "Mesh has no faces!" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < mesh->faceCount * 3; i++)
	{
		indices.push_back(mesh->face_vertexIndices->at(i));
	}
	for (unsigned int i = 0; i < mesh->faceCount * 3; i++)
	{
		uvIndices.push_back(mesh->face_uvIndices->at(i));
	}
	for (unsigned int i = 0; i < mesh->faceCount * 3; i++)
	{
		normalIndices.push_back(mesh->face_normalIndices->at(i));
	}

	//Add Color Information
	uvCoordinates.clear();
	for (unsigned int i = 0; i < mesh->texCoords->size(); i++)
	{
		//uvCoordinates.push_back(0.5f); // R
		//uvCoordinates.push_back(0.5f); // G
		//uvCoordinates.push_back(0.5f); // B

		uvCoordinates.push_back(mesh -> texCoords-> at(uvIndices[i]));
	}



	// DEBUG IMPORTANT CONDITIONS //
	std::cout << "Vertices: " << vertexPositions.size() << std::endl;
	std::cout << "Normals: " << vertexNormals.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;
	std::cout << "UV coordinates: " << uvCoordinates.size() << std::endl;

	if (vertexPositions.size() != vertexNormals.size()) 
	{
		std::cerr << "Warning: The number of vertices and normals do not match!" << std::endl;
	}
	if (vertexPositions.size() * 3 != uvCoordinates.size()) {
		std::cerr << "Warning: The number of vertices and colors do not match!" << std::endl;
	}
	if (indices.size() % 3 != 0) {
		std::cerr << "Warning: The number of indices is not a multiple of 3!" << std::endl;
	}

}
