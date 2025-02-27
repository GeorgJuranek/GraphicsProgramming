#include "MeshData.h"
#include <GL\glew.h>
#include <glm.hpp>

using namespace std;

void MeshData::init()
{
	vertices = new vector<Vertex>;
	indices = new vector<GLuint>;
	face_vertexIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_normalIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_uvIndices = new vector<GLuint>; //geändert von <GLfloat>
}

void MeshData::deInit()
{
	face_vertexIndices->clear();
	face_normalIndices->clear();
	face_uvIndices->clear();

	face_vertexIndices = nullptr;
	face_normalIndices = nullptr;
	face_uvIndices = nullptr;

}
