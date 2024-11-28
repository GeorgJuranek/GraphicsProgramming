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

	vector<GLfloat>* face_vertexIndices;
	vector<GLfloat>* face_normalIndices;
	vector<GLfloat>* face_uvIndices;

	GLint faceCount;
	string texturePath;

	void init();
	void deInit();
};


