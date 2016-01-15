#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	direction.y = sin(glm::radians(rotation.x));
	direction.z = cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
	return glm::lookAt(position,position+direction , up);
}

glm::mat4 Camera::GetProjectionMatrix(float asp)
{
	return glm::perspective(fov, 1/asp, nr, fr);
}

void Camera::MoveByLocalVector(glm::vec3 vector)
{
	glm::mat4 mat(1.0f);

	mat = glm::rotate(mat, glm::radians(-rotation.y+90), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, glm::radians(-rotation.x), glm::vec3(1, 0, 0));
	glm::vec4 v = mat*glm::vec4(vector.x, vector.y, vector.z, 0);
	position += glm::vec3(v.x, v.y, v.z);
}

void Camera::Rotate(float dx, float dy)
{
	rotation.x += dy;
	rotation.y+=dx;
	if (rotation.x > 89.0f)
		rotation.x = 89.0f;
	if (rotation.x < -89.0f)
		rotation.x = -89.0f;
}
