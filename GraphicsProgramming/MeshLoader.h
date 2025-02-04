#pragma once
#include <string>
#include "MeshData.h"
#include <fstream>
#include <sstream>

/// <summary>
/// This class is responsible for reading .obj files and parsing them into MeshData.
/// </summary>
class MeshLoader
{
public:
	static MeshLoader* getInstance();

	MeshData* loadFromFile(string filename);

private:
	MeshLoader();
	~MeshLoader();

	static MeshLoader* _pInstance;

	void parseLine(string line);
	void parseLineFaces(string line);
	void parseVertices(string line);
	void parseFace(string cv);
	void parseFaces(string line);
	void parseNormals(string line);
	void parseTexture(string line);
	void parseTextureCoordinates(string line);
	//void calculateTangentAndBitangent();

	MeshData* data;
	int faceCount;
};

