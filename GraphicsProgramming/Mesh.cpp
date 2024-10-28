#include "Mesh.h"

void Mesh::Init(Shader* shader, Material* material)
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

	GLuint indices[] = { 0, 1, 2, 0, 2, 3 }; //rectangle

	this->shader = shader;
	this->material = material;

	CreateBuffers();
	GetLightUniformIDs();
	GetMaterialUniformIDs();

}

void Mesh::Draw(Light light)
{
	glUseProgram(shader->programID);

	glUniform3fv(lightPositionID, 1, &(light.position.x));
	glUniform3fv(lightAmbientID, 1, &(light.ambient.x));
	glUniform3fv(lightDiffuseID, 1, &(light.diffuse.x));
	glUniform3fv(lightSpecularID, 1, &(light.specular.x));

	glUniform3fv(materialAmbientID, 1, &(material ->ambient.x));
	glUniform3fv(materialDiffuseID, 1, &(material->diffuse.x));
	glUniform3fv(materialSpecularID, 1, &(material->specular.x));
	glUniform1f(materialShininessID, material->shininess);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::Release()
{
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

