#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>


Renderable::Renderable(Mesh* mesh)
{
	position = glm::vec3(0);
	rotation = glm::quat(0,0,0,0);
	scale = glm::vec3(1);
	this->mesh = mesh;
}

void Renderable::Render(GLint modelLocation)
{
	glm::mat4 mat = glm::translate(globalPosition)*glm::toMat4(rotation)*glm::scale(scale);

	//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[2]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(mat));
	glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, NULL);

}

void Renderable::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}



