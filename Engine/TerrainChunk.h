#pragma once
#include "Renderable.h"

class TerrainChunk : Renderable
{
	glm::vec2 position;
	glm::vec2 size;
	int actualLOD;
	Model* lod1;
	Model* lod2;
	Model* lod3;

public:
	virtual ~TerrainChunk() override;
	bool ActualizeLOD(glm::vec2 cameraPosition);
	void Initialize(glm::vec2 position, glm::vec2 size);
	//virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
