#include "Mesh.h"
#include <gtc\matrix_transform.hpp>
#include "VertexLoader.h"

void Mesh::Init(/*const char* filePath,*/ Shader* shader, Material* material)
{
	//VertexLoader loader;
	//aiMesh* model = loader.LoadModel("C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/Pistol_02.obj");//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/GTR.obj");//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/CustomCube.obj");//

	//if (model == nullptr)
	//{
	//	//TRIANGLE DUMMY//TEST
	//	vertexPositions = {
	//		-0.5,	-0.5,	0.0f, //unten links
	//		-0.5f,	0.5,	0.0f, //oben links
	//		0.5f,	0.5,	0.0f, //oben rechts
	//		0.5,	-0.5,	0.0f, //Unten rechts
	//	};

	//	//vertexColors = {
	//	//	1.0f, 0.0f, 0.0f, //Rot
	//	//	0.0f, 1.0f, 0.0f, //Grün
	//	//	0.0f, 0.0f, 1.0f, //Blau
	//	//	1.0f, 1.0f, 0.0f, //Gelb
	//	//};

	//	//TEST all red
	//	vertexColors = {
	//		0.0f, 1.0f, 0.0f, //Grün
	//		0.0f, 1.0f, 0.0f, //Grün
	//		0.0f, 1.0f, 0.0f, //Grün
	//		0.0f, 1.0f, 0.0f, //Grün
	//	};

	//	vertexNormals = {
	//		0.0f, 0.0f, 1.0f,
	//		0.0f, 0.0f, 1.0f,
	//		0.0f, 0.0f, 1.0f,
	//		0.0f, 0.0f, 1.0f,
	//	};

	//	indices = { 0, 1, 2, 0, 2, 3 }; //rectangle

	//	std::cerr << "Failed to load Mesh from Path at Mesh.cpp\n";
	//}
	//else
	//{
	//	LoadFromAssimpMesh(model);
	//}

	//delete model;
	//model = nullptr;

	MeshLoader* loader = MeshLoader::getInstance();
	MeshData* mesh = loader->loadFromFile("C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/Pistol_02.obj");//"C:/Users/Georg/Desktop/GraphicsProgramming/GraphicsProgramming/Models/CustomCube.obj");//

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

void Mesh::Draw(Light* light)//TEST
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


	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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
	//glDeleteVertexArrays(1, &vao);//test
	positionBuffer.Delete();
	colorBuffer.Delete();
	indexBuffer.Delete();
}

void Mesh::CreateBuffers()
{
	//VAO
	glGenVertexArrays(1, &vao); //parameter: how many vao? Where to save gluint
	glBindVertexArray(vao);


	//BUFFER: positionbuffer
	positionBuffer = {};

	const GLchar* attributeName = "positionIn";
	GLuint attributeID = shader->GetAttributeLocation(attributeName);

	positionBuffer.SetAttributeId(attributeID);

	positionBuffer.CreateBufferObject();
	positionBuffer.Bind(GL_ARRAY_BUFFER);
	positionBuffer.Fill(vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);

	positionBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0);
	positionBuffer.EnableAttribute();


	//?TEST COLOR BUFFER?//
	colorBuffer = {};
	GLuint colorAttributeID = shader->GetAttributeLocation("colorIn");
	colorBuffer.SetAttributeId(colorAttributeID);
	colorBuffer.CreateBufferObject();
	colorBuffer.Bind(GL_ARRAY_BUFFER);
	colorBuffer.Fill(vertexColors.size() * sizeof(GLfloat), vertexColors.data(), GL_STATIC_DRAW);
	colorBuffer.LinkAttribute(3, GL_FLOAT, GL_FALSE, 0, 0);
	colorBuffer.EnableAttribute();


	//BUFFER: indexbuffer
	indexBuffer = {};
	indexBuffer.CreateBufferObject();
	indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.Fill(indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
	/*indexbuffer doesnt need to LinkAttribute and EnableAttribute 
	because its only for the sequence of indices*/





	//Job is done! Empty the vao
	glBindVertexArray(0);


	////
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

glm::vec3 Mesh::GetRotation(void)
{
	return _rotation;
}




//TESTEST

//void Mesh::LoadFromAssimpMesh(aiMesh* mesh) {
//	if (!mesh) {
//		std::cerr << "Null aiMesh passed to LoadFromAssimpMesh!" << std::endl;
//		return;
//	}
//
//	// Vertices
//	vertexPositions.clear();
//	if (mesh==nullptr || mesh->mNumVertices == 0) {//Hier fehler mit GTR model, kein speicherzugriff blablabla
//		std::cerr << "Mesh has no vertices!" << std::endl;
//		return;
//	}
//
//	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//		vertexPositions.push_back(mesh->mVertices[i].x);
//		vertexPositions.push_back(mesh->mVertices[i].y);
//		vertexPositions.push_back(mesh->mVertices[i].z);
//	}
//
//	vertexNormals.clear();
//	if (mesh->HasNormals()) {
//		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//			vertexNormals.push_back(mesh->mNormals[i].x);
//			vertexNormals.push_back(mesh->mNormals[i].y);
//			vertexNormals.push_back(mesh->mNormals[i].z);
//		}
//	}
//	else {
//		std::cerr << "Mesh has no normals!" << std::endl;
//		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//			vertexNormals.push_back(0.0f);  // x
//			vertexNormals.push_back(0.0f);  // y
//			vertexNormals.push_back(1.0f);  // z
//		}
//	}
//
//	// Indices
//	indices.clear();
//	if (mesh->mNumFaces == 0) {
//		std::cerr << "Mesh has no faces!" << std::endl;
//		return;
//	}
//
//	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
//
//		//indices = { 0, 1, 2, 0, 2, 3 }; //rectangle
//		aiFace face = mesh->mFaces[i];//???ERROR IS HAPPENING HERE SOMEWHERE???? CANT READ INDICES
//		if (face.mIndices == nullptr) {
//			std::cerr << "Face " << i << " has no indices!" << std::endl;
//			continue;
//		}
//		for (unsigned int j = 0; j < face.mNumIndices; j++) {
//			indices.push_back(face.mIndices[j]);
//		}
//	}
//
//	// Colors
//	vertexColors.clear();
//	if (mesh->HasVertexColors(0)) {
//		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//			aiColor4D color = mesh->mColors[0][i];
//			vertexColors.push_back(color.r);
//			vertexColors.push_back(color.g);
//			vertexColors.push_back(color.b);
//		}
//	}
//	else {
//		std::cerr << "Mesh has no vertex colors, using default white color!" << std::endl;
//		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//			vertexColors.push_back(1.0f); // R
//			vertexColors.push_back(1.0f); // G
//			vertexColors.push_back(1.0f); // B
//		}
//	}

void Mesh::LoadFromMeshData(MeshData* mesh) {
	if (!mesh) {
		std::cerr << "Null aiMesh passed to LoadFromAssimpMesh!" << std::endl;
		return;
	}

	// Vertices
	vertexPositions.clear();
	if (mesh == nullptr || mesh->vertexCount == 0) {//Hier fehler mit GTR model, kein speicherzugriff blablabla
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

	for (unsigned int i = 0; i < mesh->faceCount; i++) {

		//indices = { 0, 1, 2, 0, 2, 3 }; //rectangle
		//aiFace face = mesh->mFaces[i];//???ERROR IS HAPPENING HERE SOMEWHERE???? CANT READ INDICES
		//if (face.mIndices == nullptr) {
		//	std::cerr << "Face " << i << " has no indices!" << std::endl;
		//	continue;
		//}
		//for (unsigned int j = 0; j < face.mNumIndices; j++) {
		//	indices.push_back(face.mIndices[j]);
		//}
			indices.push_back(mesh->face_vertexIndices->at(i));
			indices.push_back(mesh->face_uvIndices->at(i));
			indices.push_back(mesh->face_normalIndices->at(i));
	}

	//TESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTESTEST
	vertexColors.clear();
	for (unsigned int i = 0; i < mesh->face_vertexIndices->size(); i++) {
		vertexColors.push_back(1.0f); // R
		//vertexColors.push_back(1.0f); // G
		//vertexColors.push_back(1.0f); // B
	}





	// Colors
	//vertexColors.clear();
	//if (mesh->HasVertexColors(0)) {
	//	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
	//		aiColor4D color = mesh->mColors[0][i];
	//		vertexColors.push_back(color.r);
	//		vertexColors.push_back(color.g);
	//		vertexColors.push_back(color.b);
	//	}
	//}
	//else {
	//	std::cerr << "Mesh has no vertex colors, using default white color!" << std::endl;
	//	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
	//		vertexColors.push_back(1.0f); // R
	//		vertexColors.push_back(1.0f); // G
	//		vertexColors.push_back(1.0f); // B
	//	}
	//}
}
