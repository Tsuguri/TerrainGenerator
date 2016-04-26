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

void Scene::RemoveRenderable(Renderable* renderable)
{
	renderables.erase(std::remove(renderables.begin(), renderables.end(), renderable), renderables.end());
}

void Scene::AddAnimatable(D3Component * animatable)
{
	animatables.push_back(animatable);
}

void Scene::RemoveAnimatable(D3Component* animatable)
{
	animatables.erase(std::remove(animatables.begin(), animatables.end(), animatable), animatables.end());
}


