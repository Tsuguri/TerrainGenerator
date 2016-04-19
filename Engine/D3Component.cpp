#include "D3Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <glm/gtx/quaternion.hpp>

void D3Component::ActualizePosition()
{
	this->globalPosition = position;
	if (parent)
	{
		glm::vec4 temp = glm::toMat4(parent->GetGlobalRotation())*glm::vec4(position.x, position.y, position.z, 0.0f);
		globalPosition = glm::vec3(temp.x, temp.y, temp.z);
		globalPosition += parent->globalPosition;

		localRotation = glm::normalize(localRotation);
		rotation = localRotation;
		if (parent)
			rotation = parent->GetGlobalRotation() * localRotation;
	}
}

void D3Component::SetLocalPosition(glm::vec3 position)
{
	this->position = position;
	globalPosition = this->position;
	if (parent)
		globalPosition += parent->globalPosition;
	for (auto child : childs)
	{
		child->ActualizePosition();
	}
}

glm::vec3 D3Component::GetLocalPostion()
{
	return position;
}

glm::vec3 D3Component::GetGlobalPosition()
{
	return globalPosition;
}

glm::quat D3Component::GetLocalRotation()
{
	return localRotation;
}
glm::quat D3Component::GetGlobalRotation()
{
	return rotation;
}

void D3Component::SetLocalRotationEuler(glm::vec3 rotation)
{
	this->localRotation = glm::quat(rotation);
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
	throw -1;
}

void D3Component::MoveByLocalVector(glm::vec3 vector)
{
	glm::mat4 mat = glm::toMat4(rotation);
	glm::vec4 v = mat*glm::vec4(vector.x, vector.y, vector.z, 0);
	SetLocalPosition(position + glm::vec3(v.x, v.y, v.z));
}

void D3Component::Rotate(float yaw, float pitch, float roll )
{
	x += pitch;
	y += yaw;
	z += roll;
	if (x > 89.0f)
		x = 89.0f;
	if (x < -89.0f)
		x = -89.0f;
	if (y > 180.0f)
		y -= 360.0f;
	if (y < -180.0f)
		y += 360.0f;

	localRotation = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
	localRotation = glm::normalize(localRotation);
	rotation = localRotation;
	if (parent)
		rotation = parent->GetGlobalRotation()*localRotation;
	for (auto child : childs)
	{
		child->ActualizePosition();
	}
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
