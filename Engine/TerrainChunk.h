#pragma once
#include "Renderable.h"
#include "PerlinNoise.h"
#include "LodInfo.h"

class TerrainChunk : public Renderable
{
	glm::ivec2 position;
	float heigh=1;
	int actualLOD;
	TerrainSystemConfiguration* configuration;
	Model** lods;
	PerlinNoise* noise;

	void CreateLOD(int i);

	//Makes lod of given index active
	void SetLOD(int lod);

	// Creates Model representing lod of given size (mesh will have 2*size^2 triangles).
	Model* GenerateLOD(int size) const;

	// Returns proper terrain height on given coordinates
	float GetHeight(float x, float y) const;

	//Actualize lod and visibility of chunk
	bool ActualiseVisiblity(glm::vec3 cameraPosition);


public:
	virtual ~TerrainChunk() override;
	// Actualize level of details according to actual position of camera.
	bool ActualizeLOD(glm::vec3 cameraPosition);
	void Initialize(glm::ivec2 position,PerlinNoise* noise, TerrainSystemConfiguration* configuration);
	glm::ivec2 GetPosition() const;
	virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
