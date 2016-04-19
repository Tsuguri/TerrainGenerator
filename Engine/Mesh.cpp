#include "Mesh.h"
#include <vector>


//Mesh::Mesh(char* path)
//{
//	indices = new std::vector<GLuint>();
//	vertices = new std::vector<Vertex>();
//	count = 0;
//	Assimp::Importer import;
//	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		//throw 0;
//		//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
//		return;
//	}
//	processNode(scene->mRootNode, scene);
//	count = indices->size();
//	SendToGPU();
//	Clear();
//}

Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> indices)
{
	this->indices = &indices;
	this->vertices = &verts;
	count = this->indices->size();
	SendToGPU();
	Clear();
}

//Mesh::Mesh(std::vector<Vertex>* verts)
//{
//	indices = new std::vector<GLuint>();
//	vertices = verts;
//	for (int i = 0; i < vertices->size(); i++)
//		indices->push_back((unsigned int)i);
//	count = indices->size();
//	SendToGPU();
//	Clear();
//}

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

void Mesh::Render()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}

//void Mesh::processNode(aiNode* node, const aiScene* scene)
//{
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		processMesh(mesh, scene);
//	}
//
//	for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], scene);
//	}
//}
//void Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
//{
//	float x, y, z, s = 0, q = 0, p = 0, u = 0, v = 0;
//
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		x = mesh->mVertices[i].x;
//		y = mesh->mVertices[i].y;
//		z = mesh->mVertices[i].z;
//		if (mesh->mNormals) // Does the model contain texture coordinates?
//		{
//			s = mesh->mNormals[i].x;
//			q = mesh->mNormals[i].y;
//			p = mesh->mNormals[i].z;
//		}
//		if (mesh->mTextureCoords[0]) // Does the model contain texture coordinates?
//		{
//			u = mesh->mTextureCoords[0][i].x;
//			v = mesh->mTextureCoords[0][i].y;
//		}
//		Vertex vex(x, y, z, s, q, p, u, v);
//		vex.standarizedNormal = glm::vec3(s, q, p);
//		vertices->push_back(vex);
//
//	}
//	for (GLuint i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//			indices->push_back((GLuint)face.mIndices[j]);
//	}
//	
//}

void Mesh::SendToGPU()
{
	//const float x0 = 1.0f;
	//const float y0 = 1.0f;
	//const float z0 = 1.0f;
	//Vertex verts[] =
	//{
	//	Vertex(-x0,-y0,1,1,1,0,1,0),
	//	Vertex(x0,-y0,1,1,0,1,1,0),
	//	Vertex(-x0,y0,1,0,1,1,1,0),
	//	Vertex(x0,y0,1,1,1,0,1,0),
	//	Vertex(-x0,-y0,-1,1,1,0,1,0),
	//	Vertex(x0,-y0,-1,1,0,1,1,0),
	//	Vertex(-x0,y0,-1,0,1,1,1,0),
	//	Vertex(x0,y0,-1,1,1,0,1,0),
	//};
	//std::vector<Vertex> vrt;
	//for (int i = 0; i < 4; i++)
	//	vrt.push_back(verts[i]);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//int p = vrt.size();
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices->size()*Vertex::VertexSize, vertices->data(), GL_STATIC_DRAW);


	GLuint positionAtt = 0;
	GLuint normalAtt = 3;
	GLuint standardNormalAtt = 1;
	GLuint centerAtt = 2;

	glVertexAttribPointer(positionAtt, Vertex::PositionCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, 0);
	glEnableVertexAttribArray(positionAtt);

	glVertexAttribPointer(normalAtt, Vertex::NormalCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, (const GLvoid*)Vertex::PositionSize);
	glEnableVertexAttribArray(normalAtt);

	glVertexAttribPointer(standardNormalAtt, Vertex::StandardNormalCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, (const GLvoid*)(Vertex::PositionSize+Vertex::NormalSize));
	glEnableVertexAttribArray(standardNormalAtt);

	glVertexAttribPointer(centerAtt, Vertex::TriangleCenterCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, (const GLvoid*)(Vertex::PositionSize + Vertex::NormalSize+Vertex::TriangleCenterSize));
	glEnableVertexAttribArray(centerAtt);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	/*GLubyte indcs[] = { 0,1,3,0,3,2,1,5,7,1,7,3,4,0,2,4,2,6,2,3,7,2,7,6,4,5,1,4,1,0,5,4,6,5,6,7 };
	std::vector<GLubyte> idc;
	for (int i = 0; i < 6; i++)
		idc.push_back(indcs[i]);*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(GLuint), indices->data(), GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indcs), indcs, GL_STATIC_DRAW);

}

void Mesh::Clear() const
{
	/*if (vertices != NULL)
		delete vertices;
	if (indices != NULL)
		delete indices;*/
}
