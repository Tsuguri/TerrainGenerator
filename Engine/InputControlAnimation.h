#pragma once

#include "D3Component.h"
#include <glm/glm.hpp>



class InputControlAnimation : public Animation
{
	bool running;
	float yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	float pitch = 0.0f;
public:
	void StartAnimation() override;
	void StopAnimation() override;
	void Animate(D3Component* object, float time) override;
	static glm::vec3 position;
};
