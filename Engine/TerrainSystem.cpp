#include "TerrainSystem.h"
#include <future>

float TerrainSystem::LODDistance1;
float TerrainSystem::LODDistance2;
float TerrainSystem::LODDistance3;

void testfun()
{

}
void testfun2(int p, int z)
{
	int g = p + z;

}

template<typename T>
bool check(std::future<T> fut)
{
	auto status = fut.wait_for(std::chrono::seconds(0));
	return status == std::future_status::ready;
}

void test()
{
	testfun();
	auto p = std::async(std::launch::async, testfun);
	auto t2 = std::async(std::launch::async,testfun2,1,2);

	//waiting

	auto status = p.wait_for(std::chrono::seconds(0));
	if (status == std::future_status::timeout) {
		// still computing
	}
	else if (status == std::future_status::ready) {
		// finished computing
	}
	else {
		// There is still std::future_status::defered
	}
}


bool TerrainSystem::CheckChunk(glm::ivec2 position,glm::vec3 camera) const
{
	return (length(camera - glm::vec3(position.x, 0, position.y)) < LODDistance3 && !chunks.count(position));

}

void TerrainSystem::UpdateChunks(glm::ivec2 position,glm::vec3 camera)
{
	std::vector<TerrainChunk*> toAdd;
	std::vector<TerrainChunk*> toRemove;

	float time = glfwGetTime();
	for(auto chunk : chunks)
	{
		
		if(!chunk.second->ActualizeLOD(camera, position))
		{
			toRemove.push_back(chunk.second);
			continue;
		}

		glm::ivec2 pos = chunk.second->GetPosition();
		if (CheckChunk(pos + glm::ivec2(chunkSize.x, 0), camera))
			toAdd.push_back( CreateChunk(pos + glm::ivec2(chunkSize.x, 0)));

		if (CheckChunk(pos + glm::ivec2(-chunkSize.x, 0), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(-chunkSize.x, 0)));
		if (CheckChunk(pos + glm::ivec2(0, chunkSize.y), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(0, chunkSize.y)));

		if (CheckChunk(pos + glm::ivec2(0, -chunkSize.y), camera))
			toAdd.push_back(CreateChunk(pos + glm::ivec2(0, -chunkSize.y)));
	}

	printf("checkpoint 1: %f\n", glfwGetTime() - time);
	printf("	added %d", (int)toAdd.size());
	if (toAdd.size() > 0)
		for (auto chunk : toAdd)
			AddChunk(chunk);
	printf("	removed %d", (int)toRemove.size());
	if(toRemove.size()>0)
		for(auto chunk : toRemove)
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
	rend->Initialize(position, chunkSize, &noise);
	return rend;
}

void TerrainSystem::Update(float time)
{
	auto position = scene->activeCamera->GetGlobalPosition();
	glm::ivec2 pos;
	glm::ivec2 camera(position.x, position.z);
	if (position.x < 0)
		position.x -= 1.0f;
	if (position.z< 0)
		position.z -= 1.0f;
	pos.x = (int)position.x / (int)chunkSize.x;
	pos.y = (int)position.z / (int)chunkSize.y;
	if (position.x < 0)
		pos.x -= 1;
	if (position.z< 0)
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



void TerrainSystem::Initialize(TurboEngine* engine)
{

	scene = engine->GetCurrentScene();

	Module::Initialize(engine);
	float time  = glfwGetTime();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			MakeChunk(glm::ivec2(i*chunkSize.x, j*chunkSize.y));
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
		scene->RemoveRenderable(rend.second);
		delete rend.second;
	}
	chunks.clear();
	printf("end of Terrain system");
}
