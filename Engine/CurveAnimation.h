#ifndef CURVEANIMATIONH
#define CURVEANIMATIONH

#include "D3Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

class CurveAnimation :public Animation
{
private:
	float speed;
	int actualPoint;
	std::vector<glm::vec3> points;
	int size;
	float actualStadium;
	bool running;
	float actualDistance;

public:
	CurveAnimation(std::vector<glm::vec3> point, float speed);
	virtual void StartAnimation() override;
	virtual void StopAnimation() override;
	virtual void Animate(D3Component* object, float time) override;
};

class InputControlAnimation : public Animation
{
	bool running;
	float yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	float pitch = 0.0f;
public:
	void StartAnimation() override;
	void StopAnimation() override;
	void Animate(D3Component* object, float time) override;
};

#endif
