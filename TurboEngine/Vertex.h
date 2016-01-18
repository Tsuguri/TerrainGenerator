#ifndef VERTEXH
#define VERTEXH
#include <glm\glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 standarizedNormal;
	glm::vec2 uv;

	static const int PositionCount = 3;
	static const int PositionSize = sizeof(glm::vec3);
	static const int NormalCount = 3;
	static const int NormalSize = sizeof(glm::vec3);
	static const int StandardNormalCount = 3;
	static const int StandardNormalSize = sizeof(glm::vec3);
	static const int UvCount = 2;
	static const int UvSize = sizeof(glm::vec2);
	static const int VertexSize = PositionSize+ UvSize +NormalSize+StandardNormalSize;

	Vertex(float x, float y, float z, float s, float t, float p, float u,float v):position(x,y,z),normal(s,t,p),uv(u,v){}
	Vertex():position(0,0,0),normal(0,0,0),uv(0,0){}
};
#endif

