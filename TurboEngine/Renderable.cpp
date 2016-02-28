#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>


ModelRenderable::ModelRenderable(Model* mesh)
{
	position = glm::vec3(0);
	rotation = glm::quat(0,0,0,0);
	scale = glm::vec3(1);
	this->model = mesh;
}

void ModelRenderable::Render(GLint modelLocation)
{
	glm::mat4 mat = glm::translate(globalPosition)*glm::toMat4(rotation)*glm::scale(scale);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(mat));

	//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);

	model->Render();

}

void ModelRenderable::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}



