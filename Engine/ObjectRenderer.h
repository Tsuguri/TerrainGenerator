#ifndef OBJECTRENDERERH
#define OBJECTRENDERERH
#include "Renderable.h"
#include <list>
#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"


class ForwardRenderer
{
private:
	int width;
	int height;

	void Initialization();
	void RenderObject(const Renderable& object, int modelLocation, int colorLocation) const;
public:
	ForwardRenderer(int windowWidth, int windowHeight);

	void ResizeWindow(int windowWidth, int windowHeight);
	void Render(const Scene& scene);


};


#endif // !OBJECTRENDERERH
