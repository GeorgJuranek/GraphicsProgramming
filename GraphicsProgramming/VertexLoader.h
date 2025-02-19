#pragma once
#include <assimp/scene.h> 
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class VertexLoader
{
public:
	aiMesh* LoadModel(const std::string& path);
};

