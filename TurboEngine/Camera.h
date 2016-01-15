#ifndef CAMERAH
#define CAMERAH
#include <glm/glm.hpp>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	float aspect;
	float nr;
	float fr;
	float fov;
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float nr, float fr, float fov, float aspect)
	{
		this->position = pos;
		this->target = target;
		this->up = up;
		this->aspect = aspect;
		this->nr = nr;
		this->fr = fr;
		this->fov = fov;

	};
};

#endif