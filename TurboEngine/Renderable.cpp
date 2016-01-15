#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


Renderable::Renderable(Mesh* mesh)
{
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(0);
	this->mesh = mesh;
}

void Renderable::Render(GLint modelLocation)
{
	glm::mat4 mat = glm::translate(position)*glm::rotate(glm::mat4(1.0f),90.0f,rotation)*glm::scale(scale);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER,mesh->vbo[0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mat));
	glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_BYTE, NULL);
}
