#pragma once
#include <vector>

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
};
