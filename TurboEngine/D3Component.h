#ifndef D3COMPONENTH
#define D3COMPONENTH
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>

class Animation;
class D3Component
{
protected:
	Animation* animation = NULL;

	D3Component* parent;
	glm::vec3 position;
	glm::vec3 globalPosition;
	glm::quat rotation;
	glm::quat localRotation;
	float x, y,z;
	std::vector<D3Component*> childs;
	virtual void ActualizePosition();
public:
	void SetLocalPosition(glm::vec3 position);
	glm::vec3 GetLocalPostion();
	glm::vec3 GetGlobalPosition();
	glm::quat GetLocalRotation();
	glm::quat GetGlobalRotation();

	void SetLocalRotationEuler(glm::vec3 rotation);
	void SetRotation(glm::quat rotation);
	void SetRotationEulerRadians(glm::vec3 rotation);

	void MoveByVector(glm::vec3 vector);
	virtual void MoveByLocalVector(glm::vec3 vector);
	virtual void Rotate(float yaw, float pitch, float roll);

	void AddChild(D3Component* child);
	void RemoveChild(D3Component* child);
	void SetParent(D3Component* parent);
	bool HasParent();
	
	void SetAnimation(Animation* anim);
	void Animate(float time);
	void SetAnimationStart(bool val) const;

};
class Animation
{
public:
	virtual void StartAnimation() = 0;
	virtual void StopAnimation() = 0;
	virtual void Animate(D3Component* object, float time) = 0;
};
#endif
