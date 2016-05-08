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
void TerrainSystem::UpdateChunks(glm::vec2 position,glm::vec3 camera)
{
	printf("%d, %d, and y: %d, %d \n", (int)position.x, (int)lastPos.x, (int)position.y, (int)lastPos.y);
	for (int i = 0; i < chunks.size(); i++)
	{
		if (!(chunks[i]->ActualizeLOD(camera,glm::vec2(0))))
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
void TerrainSystem::Update(float time)
{
	auto position = scene->activeCamera->GetGlobalPosition();
	glm::vec2 pos;
	glm::vec2 camera(position.x, position.z);
	if (position.x < 0)
		position.x -= 1.0f;
	if (position.z< 0)
		position.z -= 1.0f;
	pos.x = (int)position.x / (int)chunkSize.x;
	pos.y = (int)position.z / (int)chunkSize.y;
	if (position.x < 0)
		pos.x -= 1.0f;
	if (position.z< 0)
		pos.y -= 1.0f;

	if ((int)pos.x != (int)lastPos.x || (int)pos.y != (int)lastPos.y)
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
