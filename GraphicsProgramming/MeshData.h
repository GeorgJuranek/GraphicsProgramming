#pragma once
#include <GL\glew.h>

#include <Vector>
//#include "Vertex.h"
//#include "Vector2.h"
//#include "Vector3.h"
#include <string>

#include <glm.hpp>

//#include "Mesh.h";

using namespace std;


struct Vertex
{
	glm::vec3 position;
	glm::vec2 uvCoordinate;
	glm::vec3 normal;
};

/// <summary>
/// This class holds all data from a mesh that is being read by the MeshLoader.
/// </summary>
class MeshData //Kann raus und im Mesh direkt lagern
{
public:
	int vertexCount = 0;
	int indexCount = 0;

	vector<Vertex>* vertices;
	vector<GLuint>* indices;

	vector<glm::vec3> vertexPositions;
	vector<glm::vec3> normals;
	vector<glm::vec2> texCoords;

	vector<GLuint>* face_vertexIndices; //geändert von <GLfloat>
	vector<GLuint>* face_normalIndices; //geändert von <GLfloat>
	vector<GLuint>* face_uvIndices; //geändert von <GLfloat>

	GLint faceCount;
	string texturePath;

	void init();
	void deInit();
};


