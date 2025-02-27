#include "Mesh.h"
#include <gtc\matrix_transform.hpp>
#include "VertexLoader.h"

void Mesh::Init(Shader* shader, Material* material, string meshFilePath)
{
	MeshLoader* loader = MeshLoader::getInstance();
	data = loader->loadFromFile(meshFilePath);//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/basicCube.obj");//meshFilePath);//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/basicCube.obj");//C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/Pistol_02.obj");//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/CustomCube.obj");//

	LoadFromMeshData(data);

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

void Mesh::Draw(Light* light, Camera* camera, Texture* texture)
{
	glUseProgram(shader->programID);

	glUniform3fv(lightPositionID, 1, &(light->position.x));
	glUniform3fv(lightAmbientID, 1, &(light->ambient.x));
	glUniform3fv(lightDiffuseID, 1, &(light->diffuse.x));
	glUniform3fv(lightSpecularID, 1, &(light->specular.x));

	glUniform1f(lightAttenuationConstID, light->attenuationConst);
	glUniform1f(lightAttenuationLinearID, light->attenuationLinear);
	glUniform1f(lightAttenuationQuadID, light->attenuationQuad);

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

	glBindTexture(GL_TEXTURE_2D, texture->textureID);


	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, data->indices->size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
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

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data->vertices->size() * sizeof(Vertex), data->vertices->data(), GL_STATIC_DRAW);



	//ToDO: elementBuffer erstellen, attribute erstellen, pos uv normals/ ohne buffer klasse//

	GLuint ebo;

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indices->size() * sizeof(Vertex), data->indices->data(), GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //?
	glEnableVertexAttribArray(0);

	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvCoordinate)); //?
	glEnableVertexAttribArray(1);


	//Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); //?
	glEnableVertexAttribArray(2);


	//Job is done! Empty the vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

}
