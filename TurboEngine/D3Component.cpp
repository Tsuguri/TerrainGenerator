#include "D3Component.h"
#include <glm/gtc/matrix_transform.hpp>

void D3Component::MoveByVector(glm::vec3 vector)
{

}

void D3Component::MoveByLocalVector(glm::vec3 vector)
{
	glm::mat4 mat(1.0f);

	mat = glm::rotate(mat, glm::radians(-rotation.y + 90), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, glm::radians(-rotation.x), glm::vec3(1, 0, 0));
	glm::vec4 v = mat*glm::vec4(vector.x, vector.y, vector.z, 0);
	position += glm::vec3(v.x, v.y, v.z);
}

void D3Component::Rotate(float dx, float dy)
{
}
