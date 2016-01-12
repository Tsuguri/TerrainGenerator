#ifndef VERTEXH
#define VERTEXH

struct Vertex
{
	float x, y, z;
	float r, g, b, a;

	static const int PositionCount = 3;
	static const int PositionSize = sizeof(float)*PositionCount;
	static const int ColorCount = 4;
	static const int ColorSize = sizeof(float)*ColorCount;
	static const int VertexSize = ColorSize + PositionSize;

	Vertex(float x, float y, float z, float r, float g, float b, float a=1.0f):x(x),y(y),z(z),r(r),g(g),b(b),a(a){}
};

#endif

