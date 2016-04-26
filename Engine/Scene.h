#ifndef SCENEH
#define SCENEH
#include <glm/glm.hpp>
#include "Camera.h"
#include "Renderable.h"

class Scene
{
public:
	glm::vec3 LightDirection;
	glm::vec3 LightColor;
	Camera* activeCamera;
	std::vector<Renderable*> renderables;
	std::vector<D3Component*> animatables;
	ShaderProgram* shader;

	Scene(glm::vec3 direction, glm::vec3 color, Camera* camera) : activeCamera(camera)
	{
		
		LightDirection = direction;
		LightColor = color;
	}

	void Animate(float timePassed);
	void AddRenderable(Renderable* renderable);
	void RemoveRenderable(Renderable* renderable);
	void AddAnimatable(D3Component* animatable);
	void RemoveAnimatable(D3Component* animatable);
};

#endif
