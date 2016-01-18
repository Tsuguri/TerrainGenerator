#include "D3Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

void D3Component::SetLocalPosition(glm::vec3 position)
{
	this->position = position;
	globalPosition = this->position;
	if (parent)
		globalPosition += parent->globalPosition;
}

glm::vec3 D3Component::GetLocalPostion()
{
	return position;
}

void D3Component::SetRotation(glm::quat rotation)
{
	this->rotation = rotation;
}

void D3Component::SetRotationEulerRadians(glm::vec3 rotation)
{
	this->rotation = glm::quat(rotation);
}

void D3Component::MoveByVector(glm::vec3 vector)
{

}

void D3Component::MoveByLocalVector(glm::vec3 vector)
{
	glm::mat4 mat(1.0f);

	mat = glm::rotate(mat, glm::radians(-rotation.y + 90), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, glm::radians(-rotation.x), glm::vec3(1, 0, 0));
	glm::vec4 v = mat*glm::vec4(vector.x, vector.y, vector.z, 0);
	position += glm::vec3(v.x, v.y, v.z);
	globalPosition = position;
	if (parent)
		globalPosition += parent->position;
}

void D3Component::Rotate(float dx, float dy)
{

}
void D3Component::AddChild(D3Component* child)
{
	childs.push_back(child);
}

void D3Component::RemoveChild(D3Component* child)
{
	childs.erase(std::remove(childs.begin(), childs.end(), child), childs.end());
}

void D3Component::SetParent(D3Component* parent)
{
	if (this->parent)
		parent->RemoveChild(this);
	this->parent = parent;
	if (parent)
	{
		parent->AddChild(this);
		globalPosition=position+parent->globalPosition;
	}
}

bool D3Component::HasParent()
{
	if(parent)
	return true;
	return false;
}

void D3Component::SetAnimation(Animation* anim)
{
	if (animation)
		delete animation;
	animation = anim;
}

void D3Component::Animate(float time)
{
	if (animation)
		animation->Animate(this, time);
	for (auto child : childs)
	{
		if (child)
			child->Animate(time);
	}
}

void D3Component::SetAnimationStart(bool val) const
{
	if (!animation)
		return;
	if (val)
		animation->StartAnimation();
	else
		animation->StopAnimation();

}
