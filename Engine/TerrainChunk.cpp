#include "TerrainChunk.h"
#include "TerrainSystem.h"

TerrainChunk::~TerrainChunk()
{
	if (lod1)
		delete lod1;
	if (lod2)
		delete lod2;
	if (lod3)
		delete lod3;
	model = NULL;
}

//void TerrainChunk::Render(GLint modelLocation, GLint colorLocation) const
//{
//	//aktualizacja modelu.
//
//	Renderable::Render(modelLocation, colorLocation);
//}
bool TerrainChunk::ActualizeLOD(glm::vec2 cameraPosition)
{
	float distance = (cameraPosition - position).length();
	switch (actualLOD)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	default:

		break;
	}
	return true;
}

void TerrainChunk::Initialize(glm::vec2 position, glm::vec2 size)
{
	this->position = position;
	this->size = size;
	lod1 = lod2 = lod3 = nullptr;
}
