#ifndef MESHH
#define MESHH

//#include <vector>
#include "Vertex.h"

struct Mesh
{
	unsigned int vao;
	unsigned int vbo[3];
public:
	Mesh(Vertex vertices[]);
};
#endif // !MESHH
