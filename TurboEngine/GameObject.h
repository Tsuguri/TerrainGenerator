#ifndef GAMEOBJECTH
#define GAMEOBJECTH
#include "Renderable.h"
class GameObject
{
private :
	Renderable* renderable=nullptr;

public:
	void SetRenderable(Renderable* renderable);
};
#endif // !GAMEOBJECTH
