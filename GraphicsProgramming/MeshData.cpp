#include "MeshData.h"
#include <GL\glew.h>
#include <glm.hpp>

using namespace std;

void MeshData::init()
{
	vertices = new vector<Vertex>;
	indices = new vector<GLuint>;
	/*vertexPositions = new vector<glm::vec3>;
	normals = new vector<glm::vec3>;
	texCoords = new	vector<glm::vec2>;*/
	face_vertexIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_normalIndices = new vector<GLuint>; //geändert von <GLfloat>
	face_uvIndices = new vector<GLuint>; //geändert von <GLfloat>
}

void MeshData::deInit()
{
	//vertices->clear();
	//vertexPositions->clear();
	//normals->clear();
	//texCoords->clear();
	face_vertexIndices->clear();
	face_normalIndices->clear();
	face_uvIndices->clear();

	//vertices = nullptr;
	//vertexPositions = nullptr;
	//normals = nullptr;
	//texCoords = nullptr;
	face_vertexIndices = nullptr;
	face_normalIndices = nullptr;
	face_uvIndices = nullptr;

}
