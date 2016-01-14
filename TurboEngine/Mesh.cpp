#include "Mesh.h"
#include "glew.h"

Mesh::Mesh(Vertex vertices[])
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint positionAtt = 0;
	GLuint colorAtt = 3;
	GLuint normalAtt = 1;

	glVertexAttribPointer(positionAtt, Vertex::PositionCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, 0);
	glEnableVertexAttribArray(positionAtt);
	glVertexAttribPointer(colorAtt, Vertex::ColorCount, GL_FLOAT, GL_FALSE, Vertex::VertexSize, (const GLvoid*)Vertex::PositionSize);
	glEnableVertexAttribArray(colorAtt);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	GLubyte indices[] = { 0,1,3,4 };
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
