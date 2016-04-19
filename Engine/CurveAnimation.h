#ifndef CURVEANIMATIONH
#define CURVEANIMATIONH

#include "D3Component.h"
#include <glm/glm.hpp>
#include <vector>

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

#endif
