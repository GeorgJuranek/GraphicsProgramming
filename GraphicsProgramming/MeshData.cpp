#include "MeshData.h"
#include <GL\glew.h>

using namespace std;

void MeshData::init()
{
	//vertices = new vector<Vertex>;
	vertexPositions = new vector<GLfloat>;
	normals = new vector<GLfloat>;
	texCoords = new	vector<GLfloat>;
	face_vertexIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_normalIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_uvIndices = new vector<GLuint>; //geändert von <GLfloat>
}

void MeshData::deInit()
{
	//vertices->clear();
	vertexPositions->clear();
	normals->clear();
	texCoords->clear();
	face_vertexIndices->clear();
	face_normalIndices->clear();
	face_uvIndices->clear();

	//vertices = nullptr;
	vertexPositions = nullptr;
	normals = nullptr;
	texCoords = nullptr;
	face_vertexIndices = nullptr;
	face_normalIndices = nullptr;
	face_uvIndices = nullptr;

}
