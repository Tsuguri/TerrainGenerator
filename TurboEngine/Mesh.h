#ifndef MESHH
#define MESHH

//#include <vector>
#include "Vertex.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glew.h"

struct Mesh
{
	int count;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
	Mesh(char*);
	Mesh(std::vector<Vertex>* verts);
	Mesh(std::vector<Vertex>* vertices, std::vector<GLuint>* indices);
	~Mesh();
	void Dispose();
	void Render();
	int GetCount() const;
private:
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	void SendToGPU();
};
#endif // !MESHH
