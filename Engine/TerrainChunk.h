#pragma once
#include "Renderable.h"
#include "PerlinNoise.h"

class TerrainChunk : public Renderable
{
	glm::ivec2 position;
	glm::ivec2 size;
	int actualLOD;
	Model* lod1;
	Model* lod2;
	Model* lod3;
	PerlinNoise* noise;

	void CreateLOD1();
	void CreateLOD2();
	void CreateLOD3();
	void SetLOD(int lod);
	Model* CreateLOD(int size) const;
	float GetHeight(float x, float y) const;

	bool ActualiseVisiblity(glm::vec3 cameraPosition);


public:
	virtual ~TerrainChunk() override;
	bool ActualizeLOD(glm::vec3 cameraPosition,glm::vec2 direction);
	void Initialize(glm::ivec2 position, glm::ivec2 size,PerlinNoise* noise);
	glm::ivec2 GetPosition() const;
	virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
