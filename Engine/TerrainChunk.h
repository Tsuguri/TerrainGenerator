#pragma once
#include "Renderable.h"
#include "PerlinNoise.h"
#include "LodInfo.h"

class TerrainChunk : public Renderable
{
	glm::ivec2 position;
	float heigh=1;
	glm::ivec2 size;
	int actualLOD;
	TerrainSystemConfiguration* configuration;
	Model** lods;
	Model* lod1;
	Model* lod2;
	Model* lod3;
	PerlinNoise* noise;

	void CreateLOD1();
	void CreateLOD2();
	void CreateLOD3();

	//Makes lod of given index active
	void SetLOD(int lod);

	// Creates Model representing lod of given size (mesh will have 2*size^2 triangles).
	Model* CreateLOD(int size) const;

	// Returns proper terrain height on given coordinates
	float GetHeight(float x, float y) const;

	//Actualize lod and visibility of chunk
	bool ActualiseVisiblity(glm::vec3 cameraPosition);


public:
	virtual ~TerrainChunk() override;
	// Actualize level of details according to actual position of camera.
	bool ActualizeLOD(glm::vec3 cameraPosition);
	void Initialize(glm::ivec2 position, glm::ivec2 size,PerlinNoise* noise, TerrainSystemConfiguration* configuration);
	glm::ivec2 GetPosition() const;
	virtual void Render(GLint modelLocation, GLint colorLocation) const override;
};
