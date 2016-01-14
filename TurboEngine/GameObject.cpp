#include "GameObject.h"

void GameObject::SetRenderable(Renderable* renderable)
{
	if (this->renderable != nullptr)
	{
		this->renderable->Dispose();

	}
	this->renderable = renderable;
}
