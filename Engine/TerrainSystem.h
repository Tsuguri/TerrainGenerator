#pragma once
#include "Module.h"
#include "PerlinNoise.h"

class TerrainSystem : public Module
{
	float timeFromStart;
	Renderable* rend;
	Scene* scene;
	PerlinNoise noise;
	glm::vec2 chunkSize;
public:
	void Update(float time) override;
	void Initialize(TurboEngine* engine) override;
	void Seed(unsigned int seed,float lod1,float lod2,float lod3,glm::vec2 chunkSize);
	void EndWork() override;
	static float LODDistance1;
	static float LODDistance2;
	static float LODDistance3;
};
