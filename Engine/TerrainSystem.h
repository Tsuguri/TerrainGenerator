#pragma once
#include "Module.h"
#include "PerlinNoise.h"
#include "TerrainChunk.h"
#include <unordered_map>
#include "LodInfo.h"

// Class needed for unordered map of TerrainChunks.
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
	// Contains all active chunks in system
	std::unordered_map<glm::ivec2, TerrainChunk*> chunks;
	// Active system configuration
	TerrainSystemConfiguration configuraton;

	// Active scene containing chunks.
	Scene* scene;
	PerlinNoise noise;
	glm::ivec2 lastPos = glm::vec2(0);

	// Checks if chunk on given position should and exists. True if should be created
	bool CheckChunk(glm::ivec2 position, glm::vec3 camera) const;

	// Updates Chunks - deletes and creates new ones.
	void UpdateChunks(glm::ivec2 position, glm::vec3 camera);

	// Creates chunk on given position. Adds it to system.
	void MakeChunk(glm::ivec2 position);

	//Adds created chunk to system
	void AddChunk(TerrainChunk* chunk);

	// Removes from scene and frees pointed memory
	void DestroyChunk(TerrainChunk* chunk);

	// Creates chunk on given position. Do NOT adds it to system.
	TerrainChunk* CreateChunk(glm::ivec2 position);
public:

	// Basic constructor
	TerrainSystem(TerrainSystemConfiguration configuraton);

	// Overriden Module Update. Should not be used explicitly
	void Update(float time) override;

	//Overriden Module Initialize - For use in engine.
	void Initialize(TurboEngine* engine) override;

	// [Deprecated] to be removed
	void Seed(float lod1, float lod2, float lod3);
	//Overriden standard Module method. Cleans up everything
	void EndWork() override;
	// [Deprecated] to be removed
	static float LODDistance1;
	// [Deprecated] to be removed
	static float LODDistance2;
	// [Deprecated] to be removed
	static float LODDistance3;
};
