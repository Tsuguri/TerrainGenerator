#include "CurveAnimation.h"
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

CurveAnimation::CurveAnimation(std::vector<glm::vec3> points, float speed)
{
	actualPoint = points.size()-1;
	actualStadium = 1;
	this->points = points;
	this->speed = speed;
	size = points.size();
	actualDistance = (points[1] - points[0]).length();
	running = false;
}

void CurveAnimation::StartAnimation()
{
	running = true;
}

void CurveAnimation::StopAnimation()
{
	running = false;
}
glm::vec3 lerp(glm::vec3 vec1, glm::vec3 vec2, float point)
{
	return point*vec1 + (1 - point)*vec2;
}

void CurveAnimation::Animate(D3Component* object, float time)
{
	if (!running)
		return;
	time /= 1000.0f;
	glm::vec3 from = points[actualPoint];
	glm::vec3 to;
	if (actualPoint == size - 1)
		to = points[0];
	else
		to = points[actualPoint + 1];
	actualStadium += speed*time / actualDistance;
	if (actualStadium > 1.0f)
	{
		actualStadium = 0;
		actualPoint += 1;
		if (actualPoint >= size)
			actualPoint = 0;
		glm::vec3 rot;
		if (actualPoint == size - 1)
		{
			actualDistance = sqrt(glm::length2(to - points[0]));
			rot = to - points[0];
		}
		else
		{
			glm::vec3 temp = to - points[actualPoint + 1];
			actualDistance = sqrt(glm::length2(temp));
			rot = to - points[actualPoint + 1];

		}
		glm::vec2 angle;
		//angle.x = atan2(rot.z, rot.y);
		angle.y = atan2(rot.z, rot.x);
		if (rot.x*rot.z > 0  )
			angle.y += glm::pi<float>();
		if (rot.x == 0)
			angle.y += glm::pi<float>() / 2;
		if (rot.z == 0)
			angle.y -= glm::pi<float>() / 2;
		/*if (rot.x < 0 && rot.z<0)
			angle.y += glm::pi<float>()/2;*/
		rot.x = angle.x;
		rot.y = angle.y;
		rot.z = 0;


		object->SetRotationEulerRadians(rot);
		object->SetLocalPosition(lerp(from, to, 0));
	}
	else
		object->SetLocalPosition(lerp(from, to, 1 - actualStadium));
}

