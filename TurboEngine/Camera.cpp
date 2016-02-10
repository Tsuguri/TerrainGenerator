#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

glm::mat4 Camera::GetViewMatrix()
{
	if(watched)
		return glm::lookAt(globalPosition, watched->GetGlobalPosition(), glm::vec3(0, 1, 0));
	else
	return glm::lookAt(globalPosition, globalPosition + cameraFront, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float asp)
{
	return glm::perspective(glm::radians(fov), 1 / asp, nr, fr);
}

void Camera::WatchComponent(D3Component * obj)
{
	watched = obj;
}

//void Camera::MoveByLocalVector(glm::vec3 vector)
//{
//	glm::mat4 mat = glm::toMat4(rotation);
//	glm::vec4 v = mat*glm::vec4(vector.x, vector.y, vector.z, 0);
//	SetLocalPosition(position + glm::vec3(v.x, v.y, v.z));
//}

void Camera::Rotate(float yaw, float pitch,float roll)
{
	//x = glm::degrees(glm::pitch(rotation));
	//y = glm::degrees(glm::yaw(rotation));
	D3Component::Rotate(yaw, pitch, roll);
	cameraFront = rotation*glm::vec3(0, 0, 1.0f);
}

void Camera::ActualizePosition()
{
	D3Component::ActualizePosition();
	cameraFront = rotation*glm::vec3(0, 0, 1.0f);
}
