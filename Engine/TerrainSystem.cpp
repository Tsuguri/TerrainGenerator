#include "TerrainSystem.h"
#include <future>
#include "RangefinderSystem.h"
#include <time.h>
float TerrainSystem::LODDistance1;
float TerrainSystem::LODDistance2;
float TerrainSystem::LODDistance3;


bool TerrainSystem::CheckChunk(glm::ivec2 position, glm::vec3 camera) const
{
	return (length(camera - glm::vec3(position.x, 0, position.y)) < LODDistance3 && !chunks.count(position));

}

void TerrainSystem::UpdateChunks(glm::ivec2 position, glm::vec3 camera)
{
	std::vector<TerrainChunk*> toAdd;
	std::vector<TerrainChunk*> toRemove;

	float time = glfwGetTime();
	for (auto chunk : chunks)
	{

		if (!chunk.second->ActualizeLOD(camera))
		{
			toRemove.push_back(chunk.second);
			continue;
		}

		glm::ivec2 pos = chunk.second->GetPosition();
		if (CheckChunk(pos + glm::ivec2(configuraton.chunkSize.x, 0), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(configuraton.chunkSize.x, 0)));

		if (CheckChunk(pos + glm::ivec2(-configuraton.chunkSize.x, 0), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(-configuraton.chunkSize.x, 0)));
		if (CheckChunk(pos + glm::ivec2(0, configuraton.chunkSize.y), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(0, configuraton.chunkSize.y)));

		if (CheckChunk(pos + glm::ivec2(0, -configuraton.chunkSize.y), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(0, -configuraton.chunkSize.y)));
	}

	printf("checkpoint 1: %f\n", glfwGetTime() - time);
	printf("	added %d", (int)toAdd.size());
	if (toAdd.size() > 0)
		for (auto chunk : toAdd)
			AddChunk(chunk);
	printf("	removed %d", (int)toRemove.size());
	if (toRemove.size() > 0)
		for (auto chunk : toRemove)
		{
			chunks.erase(chunk->GetPosition());
			DestroyChunk(chunk);
		}
	printf("	checkpoint 2: %f\n", glfwGetTime() - time);
}

void TerrainSystem::MakeChunk(glm::ivec2 position)
{
	AddChunk(CreateChunk(position));
}

void TerrainSystem::AddChunk(TerrainChunk* chunk)
{
	chunks.emplace(chunk->GetPosition(), chunk);
	scene->AddRenderable(chunk);
}

void TerrainSystem::DestroyChunk(TerrainChunk* chunk)
{
	scene->RemoveRenderable(chunk);
	delete chunk;
}

TerrainChunk* TerrainSystem::CreateChunk(glm::ivec2 position)
{
	auto rend = new TerrainChunk();
	rend->Initialize(position, configuraton.chunkSize, &noise, &configuraton);
	return rend;
}

void TerrainSystem::Update(float time)
{
	auto position = scene->activeCamera->GetGlobalPosition();
	glm::ivec2 pos;
	glm::ivec2 camera(position.x, position.z);
	if (position.x < 0)
		position.x -= 1.0f;
	if (position.z < 0)
		position.z -= 1.0f;
	pos.x = (int)position.x / (int)configuraton.chunkSize.x;
	pos.y = (int)position.z / (int)configuraton.chunkSize.y;
	if (position.x < 0)
		pos.x -= 1;
	if (position.z < 0)
		pos.y -= 1;

	if (pos.x != lastPos.x || pos.y != lastPos.y)
	{
		UpdateChunks(pos, position);
	}
	lastPos = pos;
	if (engine->IsButtonPressed(79))
	{
		printf("ending work");
		engine->RemoveModule(this);
	}
}

TerrainSystem::TerrainSystem(TerrainSystemConfiguration configuraton)
{
	this->configuraton = configuraton;
	scene = nullptr;
	noise = PerlinNoise(configuraton.seed);
}


void TerrainSystem::Initialize(TurboEngine* engine)
{

	scene = engine->GetCurrentScene();

	Module::Initialize(engine);
	float ti = glfwGetTime();
	for (int i = -5; i < 6; i++)
		for (int j = -5; j < 6; j++)
		{
			MakeChunk(glm::ivec2(i*configuraton.chunkSize.x, j*configuraton.chunkSize.y));
		}
	ti = glfwGetTime() - ti;
	printf("initializing Terrain System : %f s\n", ti);

	//auto it = chunks.find(glm::ivec2(0));
	std::vector<glm::vec3> poss;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		auto x = (rand() % 100) / configuraton.frequency;
		auto y = (rand() % 100) / configuraton.frequency;
		auto h = static_cast<float>(noise.noise(8 * x, 8 * y, 0) + noise.noise(4 * x, 4 * y, 0)*0.5f + noise.noise(2 * x, 2 * y, 0)*0.25f)*configuraton.amplitude + 1;
		x *= configuraton.frequency;
		y *= configuraton.frequency;
		poss.push_back(glm::vec3(x, h, y));
	}
	RangefinderSystem::Get()->StartWorking(poss);

}

void TerrainSystem::Seed(float lod1, float lod2, float lod3)
{
	LODDistance1 = lod1;
	LODDistance2 = lod2;
	LODDistance3 = lod3;
}

void TerrainSystem::EndWork()
{
	for (auto rend : chunks)
	{
		scene->RemoveRenderable(rend.second);
		delete rend.second;
	}
	chunks.clear();
	printf("end of Terrain system");
}
