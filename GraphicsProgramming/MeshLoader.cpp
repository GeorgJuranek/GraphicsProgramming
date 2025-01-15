#include "MeshLoader.h"
#include <GL\glew.h>

using namespace std;

MeshLoader* MeshLoader::_pInstance = nullptr;

MeshLoader* MeshLoader::getInstance()
{
	if (MeshLoader::_pInstance == 0)
	{
		MeshLoader::_pInstance = new MeshLoader();
	}

	return MeshLoader::_pInstance;
}

MeshLoader::MeshLoader()
{

}

MeshLoader::~MeshLoader()
{

}

/// <summary>
/// Reads a .obj file and creates MeshData based on that.
/// </summary>
MeshData* MeshLoader::loadFromFile(string filename)
{
	data = new MeshData{};
	data->init();

	string line;
	ifstream firstRead(filename);
	ifstream secondRead(filename);

	while (getline(firstRead, line))
	{
		parseLine(line);
	}

	while (getline(secondRead, line))
	{
		parseLineFaces(line);
	}

	//calculateTangentAndBitangent();

	return data;
}

/// <summary>
/// Parses each line of the .obj file and handles it accordingly.
/// </summary>
void MeshLoader::parseLine(string line)
{
	if (line.substr(0, 2) == "v ") parseVertices(line);
	else if (line.substr(0, 2) == "vn") parseNormals(line);
	else if (line.substr(0, 2) == "vt") parseTextureCoordinates(line);
	else if (line.substr(0, 6) == "mtllib") parseTexture(line);
}

/// <summary>
/// Parses each line of the .obj file and handles it if it's a face.
/// </summary>
void MeshLoader::parseLineFaces(string line)
{
	if (line.substr(0, 1) == "f")
	{
		parseFaces(line);
	}
}

//void MeshLoader::parseFaces(string line)
//{
//	string prefix, vertex1, vertex2, vertex3;
//
//	istringstream s(line);
//	s >> prefix >> vertex1 >> vertex2 >> vertex3;
//
//	data->faceCount++;
//
//	parseFace(vertex1);
//	parseFace(vertex2);
//	parseFace(vertex3);
//}

void MeshLoader::parseFaces(string line)
{
	string prefix, vertex1, vertex2, vertex3, vertex4;

	istringstream s(line);
	s >> prefix >> vertex1 >> vertex2 >> vertex3 >> vertex4;  // vertex4 if Quad

	//data->faceCount++;

	// if Quad
	if (!vertex4.empty()) {
		parseFace(vertex1);
		parseFace(vertex2);
		parseFace(vertex3);
		parseFace(vertex4);

	}
	else
	{
		// Triangle
		parseFace(vertex1);
		parseFace(vertex2);
		parseFace(vertex3);
	}

	data->faceCount++;
}

/// <summary>
/// Parses a face.
/// First, determins where the slashes (that seperate vertex- uv- and normal index) are.
/// Secondly reads and saves the data based on what it is in a corresponding vector.
/// </summary>
void MeshLoader::parseFace(string currentVertex)
{
	//Vertex* vertex = new Vertex{};

	GLuint firstSlash = (GLuint)currentVertex.find_first_of("/");
	GLuint secondSlash = (GLuint)currentVertex.find_last_of("/");

	string vertexIndexString = currentVertex.substr(0, firstSlash);
	GLuint vertexIndex = atoi(vertexIndexString.c_str()) - 1;
	data->face_vertexIndices->push_back(vertexIndex);
	data->indexCount++;

	string uvIndexString = currentVertex.substr(firstSlash + 1, secondSlash - firstSlash + 1);
	GLuint uvIndex = atoi(uvIndexString.c_str()) - 1;
	data->face_uvIndices->push_back(uvIndex);

	string normalIndexString = currentVertex.substr(secondSlash + 1);
	GLuint normalIndex = atoi(normalIndexString.c_str()) - 1;
	data->face_normalIndices->push_back(normalIndex);

	/*vertex->position = data->vertexPositions->at(vertexIndex);
	vertex->normal = data->normals->at(normalIndex);
	vertex->uv = data->texCoords->at(uvIndex);

	data->faceCount++;
	data->vertices->push_back(*vertex);*/

	//return vertex;
	//data->vertexPositions->push_back();
}

/// <summary>
/// Parses a vertex and saves it's position.
/// </summary>
void MeshLoader::parseVertices(string line)
{
	string prefix;
	float x, y, z;

	istringstream s(line);
	s >> prefix >> x >> y >> z;

	//XMFLOAT3* v = new XMFLOAT3(x, y, z);
	data->vertexPositions->push_back(x);
	data->vertexPositions->push_back(y);
	data->vertexPositions->push_back(z);
	data->vertexCount++;
}

/// <summary>
/// Parses a normal and saves it.
/// </summary>
void MeshLoader::parseNormals(string line)
{
	string prefix;
	float x, y, z;

	istringstream s(line);
	s >> prefix >> x >> y >> z;

	//XMFLOAT3* normal = new XMFLOAT3(x, y, z);
	data->normals->push_back(x);
	data->normals->push_back(y);
	data->normals->push_back(z);
}

/// <summary>
/// Parses a uv and saves it.
/// </summary>
void MeshLoader::parseTextureCoordinates(string line)
{
	string prefix;
	GLfloat u, v;

	istringstream s(line);
	s >> prefix >> u >> v;

	//XMFLOAT2* texCoord = new XMFLOAT2(u, v);
	data->texCoords->push_back(u);
	data->texCoords->push_back(1-v);
}

/// <summary>
/// Reads the material file and gets the texture name.
/// </summary>
void MeshLoader::parseTexture(string line)
{
	string prefix, materialName;
	istringstream s(line);

	s >> prefix >> materialName;

	string materialPath = "Models/" + materialName;
	string reading;

	ifstream materialStream(materialPath);

	bool test = materialStream.is_open();

	while (getline(materialStream, reading))
	{
		if ((reading.substr(0, 6) == "map_Kd")) break;
	}

	GLuint start = (GLuint)reading.find_last_of("\\\\");
	GLuint end = (GLuint)reading.size();

	string texturePath = "Textures/" + reading.substr(start + 1, end);

	data->texturePath = texturePath;
}

/// <summary>
/// Calculate Tanget and Binormal Vector for each Vertex.
/// </summary>
//void MeshLoader::calculateTangentAndBitangent()
//{
//	for (int i = 0; i < data->vertices->size(); i += 3)
//	{
//		float position1[3], position2[3];
//		float tuVector[2], tvVector[2];
//		float den, length;
//
//		XMFLOAT3 tangent, bitangent;
//
//		position1[0] = data->vertices->at(i + 1).position.x - data->vertices->at(i).position.x;
//		position1[1] = data->vertices->at(i + 1).position.y - data->vertices->at(i).position.y;
//		position1[2] = data->vertices->at(i + 1).position.z - data->vertices->at(i).position.z;
//
//		position2[0] = data->vertices->at(i + 2).position.x - data->vertices->at(i).position.x;
//		position2[1] = data->vertices->at(i + 2).position.y - data->vertices->at(i).position.y;
//		position2[2] = data->vertices->at(i + 2).position.z - data->vertices->at(i).position.z;
//
//		tuVector[0] = data->vertices->at(i + 1).uv.x - data->vertices->at(i).uv.x;
//		tvVector[0] = data->vertices->at(i + 1).uv.y - data->vertices->at(i).uv.y;
//
//		tuVector[1] = data->vertices->at(i + 2).uv.x - data->vertices->at(i).uv.x;
//		tvVector[1] = data->vertices->at(i + 2).uv.y - data->vertices->at(i).uv.y;
//
//		den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);
//
//		tangent.x = (tvVector[1] * position1[0] - tvVector[0] * position2[0]) * den;
//		tangent.y = (tvVector[1] * position1[1] - tvVector[0] * position2[1]) * den;
//		tangent.z = (tvVector[1] * position1[2] - tvVector[0] * position2[2]) * den;
//
//		bitangent.x = (tuVector[0] * position2[0] - tuVector[1] * position1[0]) * den;
//		bitangent.y = (tuVector[0] * position2[1] - tuVector[1] * position1[1]) * den;
//		bitangent.z = (tuVector[0] * position2[2] - tuVector[1] * position1[2]) * den;
//
//		length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));
//
//		tangent.x /= length;
//		tangent.y /= length;
//		tangent.z /= length;
//
//		length = sqrt((bitangent.x * bitangent.x) + (bitangent.y * bitangent.y) + (bitangent.z * bitangent.z));
//
//		bitangent.x = bitangent.x / length;
//		bitangent.y = bitangent.y / length;
//		bitangent.z = bitangent.z / length;
//
//		data->vertices->at(i).tangent = tangent;
//		data->vertices->at(i + 1).tangent = tangent;
//		data->vertices->at(i + 2).tangent = tangent;
//
//		data->vertices->at(i).bitangent = bitangent;
//		data->vertices->at(i + 1).bitangent = bitangent;
//		data->vertices->at(i + 2).bitangent = bitangent;
//	}
//}
