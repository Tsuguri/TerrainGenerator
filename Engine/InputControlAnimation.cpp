#include "InputControlAnimation.h"
#include "TurboEngine.h"

void InputControlAnimation::StartAnimation()
{
	running = true;
}

void InputControlAnimation::StopAnimation()
{
	running = false;
}

glm::vec3 InputControlAnimation::position = glm::vec3(0);
void InputControlAnimation::Animate(D3Component* object, float time)
{
	position = object->GetGlobalPosition();
	float multiplier = glm::max(position.y, 1.0f)/10.0f;
	if(running)
	{
		TurboEngine* te = TurboEngine::GetInstance();
		if(te->IsButtonPressed(87))//w
		{
			object->MoveByLocalVector(glm::vec3(0.0f,0.0f,10.0f)*time*multiplier);
		}
		if (te->IsButtonPressed(83))//s
		{
			object->MoveByLocalVector(glm::vec3(0.0f, 0.0f, -10.0f)*time*multiplier);
		}
		if (te->IsButtonPressed(65))//a
		{
			object->MoveByLocalVector(glm::vec3(10.0f,0.0f,0.0f)*time*multiplier);
		}
		if (te->IsButtonPressed(68))//d
		{
			object->MoveByLocalVector(glm::vec3(-10.0f, 0.0f, 0.0f)*time*multiplier);
		}
		if (te->IsButtonPressed(32))
		{
			object->MoveByLocalVector(glm::vec3(0.0f, 10.0f, 0.0f)*time*multiplier);
		}
		if (te->IsButtonPressed(340))
		{
			object->MoveByLocalVector(glm::vec3(0.0f, -10.0f, 0.0f)*time*multiplier);
		}

		auto pos = te->GetMouseMove();
		if((pos.x!=0 || pos.y!=0) && te->IsMouseButtonPressed(1))
		{
			float sensitivity = 0.2f;	// Change this value to your liking
			pos.x *= sensitivity;
			pos.y *= sensitivity;

			yaw += pos.x;
			pitch += pos.y;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 front;

			object->Rotate(pos.x, pos.y, 0.0f);
		}


	}
}
