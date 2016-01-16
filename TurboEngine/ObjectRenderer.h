#ifndef OBJECTRENDERERH
#define OBJECTRENDERERH
#include "Renderable.h"
#include <list>
#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"
class ObjectRenderer
{
private:
	int width;
	int height;
	std::vector<Renderable*> renderables;
	std::list<int> meshFreePlaces;

	void Initialization();
	ShaderProgram* program;

public:
	ObjectRenderer(int windowWidth, int windowHeight, ShaderProgram* shader);
	void ResizeWindow(int windowWidth, int windowHeight);
	void Render(Camera* camera, Scene* scene);
	void Animate(float time);
	void AddRenderable(Renderable* renderable);


};


#endif // !OBJECTRENDERERH
