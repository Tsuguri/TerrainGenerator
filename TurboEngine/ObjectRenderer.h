#ifndef OBJECTRENDERERH
#define OBJECTRENDERERH
#include "Renderable.h"
#include <list>

class ObjectRenderer
{
private:
	Renderable* objects;
	std::list<int> freePlaces;
	int count;
	int size;
	void Initialization();

public:
	ObjectRenderer(int windowWidth, int windowHeight, int amount);
	void ResizeWindow(int windowWidth, int windowHeight);
	void Render();


};


#endif // !OBJECTRENDERERH
