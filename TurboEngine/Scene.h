#ifndef SCENEH
#define SCENEH
#include <glm/glm.hpp>

class Scene
{
public:
	glm::vec3 LightDirection;
	glm::vec3 LightColor;
	int lightningType;
	Scene(glm::vec3 direction, glm::vec3 color,int type)
	{
		LightDirection = direction;
		LightColor = color;
		lightningType = type;
	}
	void NextType()
	{
		lightningType = (lightningType + 1) % 3;
	}
};

#endif