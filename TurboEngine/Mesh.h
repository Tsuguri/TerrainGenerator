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
	unsigned int vao;
	unsigned int vbo[3];
	std::vector<Vertex>* vertices;
	std::vector<GLuint>* indices;
public:
	Mesh(char*);
	Mesh(std::vector<Vertex>* verts);
	~Mesh();
	void Dispose();
	int GetCount() const;
private:
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	void SendToGPU();
	void Clear() const;
};
#endif // !MESHH
