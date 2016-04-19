#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>


Renderable::Renderable()
{
	position = glm::vec3(0);
	rotation = glm::quat(0, 0, 0, 0);
	scale = glm::vec3(1);
}

Renderable::Renderable(Model* mesh)
{
	position = glm::vec3(0);
	rotation = glm::quat(0,0,0,0);
	scale = glm::vec3(1);
	this->model = mesh;
}

void Renderable::Render(GLint modelLocation, GLint colorLocation) const
{
	glm::mat4 mat = glm::translate(globalPosition)*glm::toMat4(rotation)*glm::scale(scale);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(mat));
	glUniform3fv(colorLocation, 1, glm::value_ptr(color));

	model->Render();

}

void Renderable::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}



