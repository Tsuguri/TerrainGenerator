#include "Mesh.h"
#include "glew.h"
#include <vector>


Mesh::Mesh(char* path)
{
	indices = new std::vector<int>();
	vertices = new std::vector<Vertex>();
	count = 0;
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		//throw 0;
		//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	processNode(scene->mRootNode, scene);
	SendToGPU();
	Clear();
}
Mesh::Mesh(std::vector<Vertex>* verts)
{
	indices = new std::vector<int>();
	vertices = verts;
	for (int i = 0; i < vertices->size(); i++)
		indices->push_back(i);
	count = indices->size();
	SendToGPU();
	Clear();
}

Mesh::~Mesh()
{
	if (vbo > 0)
		Dispose();
}

void Mesh::Dispose()
{
	glDeleteBuffers(3, vbo);
	glDeleteVertexArrays(1, &vao);
}

int Mesh::GetCount() const
{
	return count;
}

void Mesh::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
void Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
	float x, y, z, s = 0, q = 0, p = 0, u = 0, v = 0;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		x = mesh->mVertices[i].x;
		y = mesh->mVertices[i].y;
		z = mesh->mVertices[i].z;
		if (mesh->mNormals) // Does the mesh contain texture coordinates?
		{
			s = mesh->mNormals[i].x;
			q = mesh->mNormals[i].y;
			p = mesh->mNormals[i].z;
		}
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			u = mesh->mTextureCoords[0][i].x;
			v = mesh->mTextureCoords[0][i].y;
		}
		Vertex vex(x, y, z, s, q, p, u, v);
		vertices->push_back(vex);

	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices->push_back(face.mIndices[j]);
	}
	count += indices->size();
}

void Mesh::SendToGPU()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices->size(), &vertices[0], GL_STATIC_DRAW);

	GLuint positionAtt = 0;
	GLuint colorAtt = 3;
	GLuint normalAtt = 1;

	glVertexAttribPointer(positionAtt, Vertex::PositionCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, 0);
	glEnableVertexAttribArray(positionAtt);
	glVertexAttribPointer(normalAtt, Vertex::NormalCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, (const GLvoid*)Vertex::PositionSize);
	glEnableVertexAttribArray(normalAtt);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void Mesh::Clear() const
{
	delete vertices;
	delete indices;
}
