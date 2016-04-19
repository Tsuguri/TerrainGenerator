#pragma once
#include "D3Component.h"

class BezierPositionAnimation : public Animation
{
private:
	float timePassed;
	bool shouldAnimate;
public:
	BezierPositionAnimation(float startTime);
	virtual void StartAnimation() override;
	virtual void StopAnimation() override;
	virtual void Animate(D3Component* object,float time) override;
};
