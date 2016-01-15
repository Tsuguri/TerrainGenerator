#ifndef MODELH
#define MODELH
#include <string>
#include "glew.h"
#include <vector>
#include "Mesh.h"

class Model
{
public:
	/*  Functions   */
	Model(GLchar* path)
	{
		this->loadModel(path);
	}
	void Draw();
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
#endif
