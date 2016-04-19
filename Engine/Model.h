#ifndef MODELH
#define MODELH
#include "D3Component.h"
#include "Mesh.h"

class Model : public D3Component
{
	std::vector<Mesh*> meshes;
public:
	Model(char* path);
	Model(Mesh* mesh);
	void Render();
	std::string directory;

};
#endif
