#ifndef CAMERAH
#define CAMERAH
#include <glm/glm.hpp>
#include "D3Component.h"

class Camera : public D3Component
{
public:

	glm::vec3 up;
	glm::vec3 cameraFront;// = glm::vec3(0.0f, 0.0f, 1.0f);
	float nr;
	float fr;
	float fov;
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float asp);
	Camera(glm::vec3 pos, glm::quat rotation, glm::vec3 up, float nr, float fr, float fov)
	{
		globalPosition=position= pos;
		cameraFront = rotation* glm::vec3(0,0,1.0f);
		this->up = up;
		this->rotation = rotation;
		x = glm::degrees(glm::pitch(rotation));
		y = glm::degrees(glm::yaw(rotation));
		/*x = glm::pitch(rotation);
		y = glm::yaw(rotation);
		SetLocalPosition(pos);
		this->rotation = rotation;
		this->rotation.y;*/
		this->up = up;
		this->nr = nr;
		this->fr = fr;
		this->fov = fov;

	};
	void Rotate(float yaw, float pitch, float roll=0) override;
	void ActualizePosition() override;
	//void MoveByLocalVector(glm::vec3 vector) override;

};

#endif