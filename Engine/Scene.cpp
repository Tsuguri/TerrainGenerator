#include "Scene.h"

void Scene::Animate(float timePassed)
{
	for (auto animatable : animatables)
		animatable->Animate(timePassed);
}

void Scene::AddRenderable(Renderable * renderable)
{
	renderables.push_back(renderable);
}

void Scene::AddAnimatable(D3Component * renderable)
{
	animatables.push_back(renderable);
}
