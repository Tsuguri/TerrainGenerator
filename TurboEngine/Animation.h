#ifndef ANIMATIONH
#define ANIMATIONH

#include "D3Component.h"

class Animation
{
public:
	virtual void StartAnimation()=0;
	virtual void StopAnimation() = 0;
	virtual void Animate(D3Component* object,float time) = 0;
};

#endif
