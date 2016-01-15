#ifndef CAMERAH
#define CAMERAH
#include <glm/glm.hpp>
#include "D3Component.h"

class Camera : public D3Component
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 up;
	float nr;
	float fr;
	float fov;
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float asp);
	Camera(glm::vec3 pos, glm::vec3 rotation, glm::vec3 up, float nr, float fr, float fov)
	{
		this->position = pos;
		this->rotation = rotation;
		this->rotation.y += 90;
		this->up = up;
		this->nr = nr;
		this->fr = fr;
		this->fov = fov;

	};
	void Rotate(float dx, float dy) override;
	void MoveByLocalVector(glm::vec3 vector) override;

};

#endif