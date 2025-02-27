#include "MeshLoader.h"
#include <GL\glew.h>

#include "Mesh.h"

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
	faceCount = 0;

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

	for (int i = 0; i < faceCount; i++)
	{
		data->indices->push_back(i);
	}

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


void MeshLoader::parseFaces(string line)
{
	string prefix, vertex1, vertex2, vertex3, vertex4;

	istringstream s(line);
	s >> prefix >> vertex1 >> vertex2 >> vertex3 >> vertex4;  // vertex4 if Quad

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
	faceCount++;

	Vertex* vertex = new Vertex{};

	GLuint firstSlash = (GLuint)currentVertex.find_first_of("/");
	GLuint secondSlash = (GLuint)currentVertex.find_last_of("/");

	string vertexIndexString = currentVertex.substr(0, firstSlash);
	GLuint vertexIndex = atoi(vertexIndexString.c_str()) - 1;
	vertex->position = (data->vertexPositions[vertexIndex]);

	string uvIndexString = currentVertex.substr(firstSlash + 1, secondSlash - firstSlash + 1);
	GLuint uvIndex = atoi(uvIndexString.c_str()) - 1;
	vertex->uvCoordinate = data->texCoords[uvIndex];

	string normalIndexString = currentVertex.substr(secondSlash + 1);
	GLuint normalIndex = atoi(normalIndexString.c_str()) - 1;
	vertex->normal = data->normals[normalIndex];


	data->vertices->push_back(*vertex);

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

	glm::vec3 position = glm::vec3(x, y, z);

	data->vertexPositions.push_back(position);

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

	glm::vec3 normal = glm::vec3(x, y, z);

	data->normals.push_back(normal);
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

	glm::vec2 uv = glm::vec2(u, 1-v);
	data->texCoords.push_back(uv);

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


