#include "TerrainSystem.h"

float TerrainSystem::LODDistance1;
float TerrainSystem::LODDistance2;
float TerrainSystem::LODDistance3;


void TerrainSystem::Update(float time)
{
	timeFromStart += time;
	auto position = scene->activeCamera->GetGlobalPosition();
	glm::vec2 pos;
	glm::vec2 camera(position.x, position.z);
	pos.x = (int)position.x % (int)chunkSize.x;
	pos.y = (int)position.y % (int)chunkSize.y;
	if ((int)pos.x != (int)lastPos.x || (int)pos.y != (int)lastPos.y)
	{
		for (int i = 0; i < chunks.size(); i++)
		{
			if (!(chunks[i]->ActualizeLOD(camera)))
			{
				TerrainChunk* temp = chunks[i];
				if (chunks.size() > 1)
				{
					chunks[i] = chunks[chunks.size() - 1];
				}
				chunks.pop_back();
				scene->RemoveRenderable(temp);
				delete temp;
			}
		}
	}
	lastPos = pos;
	if (timeFromStart > 2)
	{
		timeFromStart -= 2;
		//printf("Terrain system update\n");
	}
	if (engine->IsButtonPressed(79))
	{
		printf("ending work");
		engine->RemoveModule(this);
	}
}

void TerrainSystem::Initialize(TurboEngine* engine)
{

	scene = engine->GetCurrentScene();

	Module::Initialize(engine);
	TerrainChunk* rend;
	float time  = glfwGetTime();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			rend = new TerrainChunk();
			rend->Initialize(glm::vec2(i*chunkSize.x, j*chunkSize.y), chunkSize, &noise);
			chunks.push_back(rend);
			scene->AddRenderable(rend);
		}
	time = glfwGetTime() - time;
	printf("initializing Terrain System : %f s\n",time);
}

void TerrainSystem::Seed(unsigned seed, float lod1, float lod2, float lod3, glm::vec2 chunkSize)
{
	noise = PerlinNoise(seed);
	LODDistance1 = lod1;
	LODDistance2 = lod2;
	LODDistance3 = lod3;
	this->chunkSize = chunkSize;

}

void TerrainSystem::EndWork()
{
	for (auto rend : chunks)
	{
		scene->RemoveRenderable(rend);
		delete rend;
	}
	chunks.clear();
	printf("end of Terrain system");
}
