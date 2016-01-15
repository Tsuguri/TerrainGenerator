#include "Renderable.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


Renderable::Renderable(Model* model)
{
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
	this->model = model;
}

void Renderable::Render(GLint modelLocation)
{
	//glm::mat4 mat = glm::translate(position);// *glm::rotate(glm::mat4(1.0f), 90.0f, rotation)*glm::scale(scale);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(mat));
	//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	model->Draw();
	//printf("syf");
}
