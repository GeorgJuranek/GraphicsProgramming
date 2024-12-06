#pragma once
#include <GL\glew.h>

#include <Vector>
//#include "Vertex.h"
//#include "Vector2.h"
//#include "Vector3.h"
#include <string>

using namespace std;

/// <summary>
/// This class holds all data from a mesh that is being read by the MeshLoader.
/// </summary>
class MeshData
{
public:
	int vertexCount = 0;
	int indexCount = 0;

	//vector<Vertex>* vertices;
	vector<GLfloat>* vertexPositions;
	vector<GLfloat>* normals;
	vector<GLfloat>* texCoords;

	vector<GLuint>* face_vertexIndices; //geändert von <GLfloat>
	vector<GLuint>* face_normalIndices; //geändert von <GLfloat>
	vector<GLuint>* face_uvIndices; //geändert von <GLfloat>

	GLint faceCount;
	string texturePath;

	void init();
	void deInit();
};


