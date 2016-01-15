#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, target, up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(fov, aspect, nr, fr);
}
