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
	void CreateLOD2();
	void CreateLOD3();
	void SetLOD(int lod);
	Model* CreateLOD(int size) const;
	float GetHeight(float x, float y) const;
	void ActualiseVisiblity(glm::vec3 cameraPosition);


public:
	virtual ~TerrainChunk() override;
	void ActualizeLOD(glm::vec3 cameraPosition,glm::vec2 direction);
	void Initialize(glm::vec2 position, glm::vec2 size,PerlinNoise* noise);
	//virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
