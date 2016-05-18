#pragma once
#include "Module.h"
#include "PerlinNoise.h"
#include "TerrainChunk.h"
#include <unordered_map>
#include "LodInfo.h"
namespace std
{
	template <>
	struct hash<glm::ivec2>
	{
		size_t operator()(glm::ivec2 const & x) const noexcept
		{
			int size = x.length();
			std::size_t seed = size;

			for (int i = 0; i < size; i++)
			{
				seed ^= x[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);

			}
			return seed;
		}
	};
}


class TerrainSystem : public Module
{
	std::unordered_map<glm::ivec2, TerrainChunk*> chunks;
	TerrainSystemConfiguration configuraton;

	Scene* scene;
	PerlinNoise noise;
	glm::ivec2 chunkSize;
	glm::ivec2 lastPos = glm::vec2(0);

	bool CheckChunk(glm::ivec2 position, glm::vec3 camera) const;
	void UpdateChunks(glm::ivec2 position, glm::vec3 camera);
	void MakeChunk(glm::ivec2 position);
	void AddChunk(TerrainChunk* chunk);
	void DestroyChunk(TerrainChunk* chunk);
	TerrainChunk* CreateChunk(glm::ivec2 position);
public:
	TerrainSystem(TerrainSystemConfiguration configuraton);
	void Update(float time) override;
	void Initialize(TurboEngine* engine) override;

	void Seed(unsigned int seed, float lod1, float lod2, float lod3, glm::vec2 chunkSize);
	void EndWork() override;
	static float LODDistance1;
	static float LODDistance2;
	static float LODDistance3;
};
