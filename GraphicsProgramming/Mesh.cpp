#include "Mesh.h"
#include <gtc\matrix_transform.hpp>

void Mesh::Init(/*const char* filePath,*/ Shader* shader, Material* material)
{
	//TRIANGLE DUMMY//TEST
	vertexPositions = {
		-0.5,	-0.5,	0.0f,
		-0.5f,	0.5,	0.0f,
		0.5f,	0.5,	0.0f,
		0.5,	-0.5,	0.0f,
	};

	vertexColors = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
	};

	vertexNormals = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	GLuint indices[] = { 0, 1, 2, 0, 2, 3 }; //rectangle

	this->shader = shader;
	this->material = material;

	CreateBuffers();
	GetLightUniformIDs();
	GetMaterialUniformIDs();
	cameraPositionID = shader->GetUniformLocation("cameraPosition");

	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_model = glm::mat4(1.0);



	//LoadMesh(filePath);
	//SetShader(shader);
	//SetMaterial(material);

	//CreateBuffers();
	//GetLightUniformIDs();
	//GetMaterialUniformIDs();
	//GetMVPUniformIDs();
	//cameraPositionID = shader->GetUniformLocation("cameraPosition");

	//_position = glm::vec3(0.0f, 0.0f, 0.0f);
	//_model = glm::mat4(1.0);


}

//void Mesh::LoadMesh(const char* filePath)
//{
//	scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
//
//	vertexPositions.clear();
//
//	for (int i = 0; i < scene->mMeshes[0]->mNumVerices; i++)
//	{
//		const aiVector3D position = scene->mMeshes[0]->mVertices[i];
//
//		vertexPositions.push_back(position.x);
//		vertexPositions.push_back(position.y);
//		vertexPositions.push_back(position.z);
//	}
//}

void Mesh::Draw(Light light)
{
	glUseProgram(shader->programID);

	glUniform3fv(lightPositionID, 1, &(light.position.x));
	glUniform3fv(lightAmbientID, 1, &(light.ambient.x));
	glUniform3fv(lightDiffuseID, 1, &(light.diffuse.x));
	glUniform3fv(lightSpecularID, 1, &(light.specular.x));

	glUniform1f(lightAttenuationConstID, light->attenuationConst);
	glUniform1f(lightAttenuationLinearID, light->attenuationLinear);
	glUniform1f(lightAttenuationQuadID, light->attenuationQuad);

	glUniform3fv(materialAmbientID, 1, &(material ->ambient.x));
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
	//glDeleteVertexArrays(1, &vao);//test
	positionBuffer.Delete();
	colorBuffer.Delete();
	indexBuffer.Delete();
}

void Mesh::CreateBuffers()
{
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	positionBuffer = {};
	const GLchar* attributeName = "positionIn";
	GLuint attributeID = shader->GetAttributeLocation(attributeName);
	positionBuffer.CreateBufferObject();
	positionBuffer.Bind(GL_ARRAY_BUFFER);
	positionBuffer.Fill(sizeof(vertexPositions), &(vertexPositions), GL_STATIC_DRAW);
	positionBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0);
	positionBuffer.EnableAttribute();

	indexBuffer = {};
	indexBuffer.CreateBufferObject();
	indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.Fill(sizeof(indices), &(indices), GL_STATIC_DRAW);
	glBindVertexArray(0);


	//
	//colorBuffer = {};
	//GLuint colorAttributeID = shader->GetAttributeLocation("colorIn");
	//colorBuffer.CreateBufferObject();
	//colorBuffer.Bind(GL_ARRAY_BUFFER);
	//colorBuffer.Fill(sizeof(vertexColors), &(vertexColors), GL_STATIC_DRAW);
	//colorBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0);
	//colorBuffer.EnableAttribute();
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
