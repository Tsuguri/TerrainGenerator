#pragma once
#include <vector>
#include <glm/glm.hpp>
struct LodInfo
{
	int size;
	std::vector<int> distances;
	std::vector<int> sizes;
};

struct TerrainSystemConfiguration
{
	LodInfo lods;
	unsigned seed;
	float amplitude;
	float frequency;
	glm::ivec2 chunkSize;
};
