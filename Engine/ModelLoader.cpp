#include "ModelLoader.h"

#include "glew.h"
#include <fstream>

//std::vector<Vertex>* ModelLoader::LoadModel(char * path)
//{
//	Assimp::Importer import;
//	std::ifstream input(path);
//	if (input.fail())
//		return nullptr;
//	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		//throw 0;
//		//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
//		return &std::vector<Vertex>();
//	}
//	std::vector<Vertex> vertices;
//	processNode(scene->mRootNode,&vertices, scene);
//	return &vertices;
//}
//void ModelLoader::processNode(aiNode* node,std::vector<Vertex>* vertices, const aiScene* scene)
//{
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		processMesh(mesh, vertices, scene);
//	}
//
//	for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], vertices, scene);
//	}
//}
//void ModelLoader::processMesh(aiMesh* mesh, std::vector<Vertex>* vertices, const aiScene* scene)
//{
//	float x, y, z, s = 0, q = 0, p = 0, u=0, v=0;
//	
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		x = mesh->mVertices[i].x;
//		y = mesh->mVertices[i].y;
//		z = mesh->mVertices[i].z;
//		if (mesh->mNormals) // Does the mesh contain texture coordinates?
//		{
//			s = mesh->mNormals[i].x;
//			q = mesh->mNormals[i].y;
//			p = mesh->mNormals[i].z;
//		}
//		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
//		{
//			u = mesh->mTextureCoords[0][i].x;
//			v = mesh->mTextureCoords[0][i].y;
//		}
//		Vertex vex(x,y,z,s,q,p,u,v);
//			vertices->push_back(vex);
//	}
//}
