#include "BezierPositionAnimation.h"

BezierPositionAnimation::BezierPositionAnimation(float startTime)
{
	timePassed = startTime;
	shouldAnimate = false;
}

void BezierPositionAnimation::StartAnimation()
{
	shouldAnimate = true;
}

void BezierPositionAnimation::StopAnimation()
{
	shouldAnimate = false;
}

void BezierPositionAnimation::Animate(D3Component* object,float time)
{
	if (!shouldAnimate)
		return;
	timePassed += time/300.0f;
	object->position.y = sin(timePassed);
}
