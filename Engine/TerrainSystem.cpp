#include "TerrainSystem.h"

float TerrainSystem::LODDistance1;
float TerrainSystem::LODDistance2;
float TerrainSystem::LODDistance3;

Renderable* CreateRend()
{
	std::vector<Vertex>* vecs = new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();
	vecs->push_back(Vertex(-20, 0, -20, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(-20, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, -20, 0, 1, 0, 1, 0));
	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	Renderable* rend = new Renderable(new Model(new Mesh(*vecs, *indices)));
	rend->color = glm::vec3(0.2f, 0.2f, 0.2f);
	return rend;
}


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
	rend = CreateRend();
	scene = engine->GetCurrentScene();
	scene->AddRenderable(rend);
	Module::Initialize(engine);
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
