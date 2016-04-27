#pragma once
#include "Renderable.h"
#include "PerlinNoise.h"

class TerrainChunk : public Renderable
{
	glm::vec2 position;
	glm::vec2 size;
	int actualLOD;
	Model* lod1;
	Model* lod2;
	Model* lod3;
	PerlinNoise* noise;

	void CreateLOD1();
	float GetHeight(float x, float y);
public:
	virtual ~TerrainChunk() override;
	bool ActualizeLOD(glm::vec2 cameraPosition);
	void Initialize(glm::vec2 position, glm::vec2 size,PerlinNoise* noise);
	//virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
