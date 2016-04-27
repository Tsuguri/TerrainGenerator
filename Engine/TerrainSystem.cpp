#include "TerrainSystem.h"

float TerrainSystem::LODDistance1;
float TerrainSystem::LODDistance2;
float TerrainSystem::LODDistance3;


void TerrainSystem::Update(float time)
{
	timeFromStart += time;
	if(timeFromStart>2)
	{
		timeFromStart -= 2;
		//printf("Terrain system update\n");
	}
	if(engine->IsButtonPressed(79))
	{
		printf("ending work");
		engine->RemoveModule(this);
	}
}

void TerrainSystem::Initialize(TurboEngine* engine)
{
	
	scene = engine->GetCurrentScene();
	
	Module::Initialize(engine);
	rend = new TerrainChunk();
	rend->Initialize(glm::vec2(0, 0), chunkSize, &noise);
	scene->AddRenderable(rend);
	printf("initializing Terrain System");
}

void TerrainSystem::Seed(unsigned seed, float lod1, float lod2, float lod3,glm::vec2 chunkSize)
{
	noise = PerlinNoise(seed);
	LODDistance1 = lod1;
	LODDistance2 = lod2;
	LODDistance3 = lod3;
	this->chunkSize = chunkSize;

}

void TerrainSystem::EndWork()
{
	scene->RemoveRenderable(rend);
	delete rend;
	printf("end of Terrain system");
}
