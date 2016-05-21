#pragma once
#include "Module.h"

class RangefinderSystem : public Module
{
	Scene* scene;
	std::vector<Renderable*> objects;
	static RangefinderSystem* instance;
	bool working = false;
public:
	static RangefinderSystem* Get();
	RangefinderSystem();
	void Update(float time) override;
	void Initialize(TurboEngine* engine) override;
	void EndWork() override;
	void StartWorking(std::vector<glm::vec3> positions);
};
