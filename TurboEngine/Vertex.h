#ifndef VERTEXH
#define VERTEXH
#include <glm\glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;

	static const int PositionCount = 3;
	static const int PositionSize = sizeof(glm::vec3);
	static const int ColorCount = 4;
	static const int ColorSize = sizeof(glm::vec4);
	static const int NormalCount = 3;
	static const int NormalSize = sizeof(glm::vec3);
	static const int VertexSize = PositionSize+ColorSize+NormalSize;

	Vertex(float x, float y, float z, float r, float g, float b, float a=1.0f):position(x,y,z),color(r,g,b,a){}
};
#endif

