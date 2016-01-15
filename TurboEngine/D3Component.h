#ifndef D3COMPONENTH
#define D3COMPONENTH
#include <glm/glm.hpp>

class D3Component
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	void MoveByVector(glm::vec3 vector);
	virtual void MoveByLocalVector(glm::vec3 vector);
	virtual void Rotate(float dx, float dy);
};
#endif
