#include "VertexLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "glm.hpp"

//struct Vertex {
//    glm::vec3 position;
//    glm::vec3 normal;
//};
//
//std::vector<Vertex> vertices;

aiMesh* VertexLoader::LoadModel(const std::string& path) 
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    aiMesh* mesh = scene->mMeshes[0];


    return mesh;
}
