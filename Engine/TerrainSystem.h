#pragma once
#include "Module.h"
#include "PerlinNoise.h"
#include "TerrainChunk.h"

class TerrainSystem : public Module
{
	float timeFromStart;
	std::vector<TerrainChunk*> chunks;
	Scene* scene;
	PerlinNoise noise;
	glm::vec2 chunkSize;
	glm::vec2 lastPos = glm::vec2(0);

	void UpdateChunks(glm::vec2 position,glm::vec3 camera);
public:
	void Update(float time) override;
	void Initialize(TurboEngine* engine) override;
	void Seed(unsigned int seed,float lod1,float lod2,float lod3,glm::vec2 chunkSize);
	void EndWork() override;
	static float LODDistance1;
	static float LODDistance2;
	static float LODDistance3;
};
