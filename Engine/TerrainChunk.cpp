#include "TerrainChunk.h"
#include "TerrainSystem.h"
#include "PerlinNoise.h"

class Triangle
{
public:
	Vertex one;
	Vertex two;
	Vertex three;

};
class Quad
{
public:
	Triangle up;
	Triangle down;
};

void TerrainChunk::CreateLOD(int i)
{
	if (lods[i])
		return;
	lods[i] = GenerateLOD(configuration->lods.sizes[i]);
}

void TerrainChunk::SetLOD(int lod)
{
	CreateLOD(lod);
	model = lods[lod];
	actualLOD = lod;
}

Model* TerrainChunk::GenerateLOD(int size) const
{
	float fre = configuration->frequency;//frequency
	float ts = configuration->chunkSize.x / (float)size;
	float** heights = new float*[size+1];
	float ampl = configuration->amplitude;
	for (int i = 0; i < size + 1;i++)
	{
		heights[i] = new float[size + 1];
		for (int j = 0; j < size + 1; j++)
			heights[i][j] = GetHeight((position.x + i*ts) / fre, (position.y + ts*j) / fre)*ampl;
	}
	Quad** quads = new Quad*[size];
	for (int i = 0; i < size; i++)
		quads[i] = new Quad[size];
	Quad temp;
	glm::vec3 norm;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp = quads[i][j];

			temp.up.one.position = glm::vec3((position.x + ts* i), heights[i][j], (position.y + ts*j));
			temp.up.two.position = glm::vec3((position.x + ts*(i + 1)), heights[i + 1][j], (position.y + ts*j));
			temp.up.three.position = glm::vec3((position.x + ts*(i + 1)), heights[i + 1][j + 1], (position.y + ts*(j + 1)));

			norm = glm::normalize(glm::cross(temp.up.two.position - temp.up.three.position, temp.up.one.position - temp.up.two.position));
			temp.up.one.normal = temp.up.two.normal = temp.up.three.normal = norm;

			temp.down.one.position = glm::vec3((position.x + ts*i),heights[i][j], (position.y + ts* j));
			temp.down.two.position = glm::vec3((position.x + ts*i), heights[i][j+1], (position.y + ts*(j + 1)));
			temp.down.three.position = glm::vec3((position.x + ts*(i + 1)), heights[i + 1][j + 1], (position.y + ts*( j + 1)));


			norm = glm::normalize(glm::cross(temp.down.one.position - temp.down.two.position, temp.down.two.position - temp.down.three.position));
			temp.down.one.normal = temp.down.two.normal = temp.down.three.normal = norm;

			quads[i][j] = temp;
		}
	}

	std::vector<Vertex>* vecs = new std::vector<Vertex>();
	vecs->reserve((size + 1)*(size + 1));
	std::vector<GLuint>* indices = new std::vector<GLuint>();
	indices->reserve((size + 1)*(size + 1));

	int k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			vecs->push_back(quads[i][j].up.three);
			vecs->push_back(quads[i][j].up.two);
			vecs->push_back(quads[i][j].up.one);
			vecs->push_back(quads[i][j].down.one);
			vecs->push_back(quads[i][j].down.two);
			vecs->push_back(quads[i][j].down.three);
			for (int z = 0; z < 6; z++)
			{
				indices->push_back(k);
				k++;
			}
		}
	}

	auto tmp = new Model(new Mesh(*vecs, *indices));
	for (int i = 0; i < size; i++)
		delete quads[i];
	for (int i = 0; i < size + 1; i++)
		delete heights[i];
	delete heights;
	delete quads;
	delete vecs;
	delete indices;
	return tmp;
}

float TerrainChunk::GetHeight(float x, float y) const
{
	return static_cast<float>(noise->noise(8 * x, 8 * y, 0) + noise->noise(4 * x, 4 * y, 0)*0.5f + noise->noise(2 * x, 2 * y, 0)*0.25f);
}

bool TerrainChunk::ActualiseVisiblity(glm::vec3 cameraPosition)
{
	glm::vec2 temp = (position + configuration->chunkSize / 2);
	float distance = glm::length(cameraPosition - glm::vec3(temp.x, cameraPosition.y, temp.y));
	float time = glfwGetTime();
	if(actualLOD<0)
	{
		int i;
		for (i = configuration->lods.size-1; i >=0; i--)
			if (distance>configuration->lods.distances[i])
				break;
		i++;
		if (i == configuration->lods.size)
			return false;
		SetLOD(i);
		return true;
	}

	if(distance> configuration->lods.distances[actualLOD]+5)
	{
		if (actualLOD == configuration->lods.size - 1)
		{
			return false;
		}
		else
			SetLOD(actualLOD + 1);
	}
	if(actualLOD>0 && distance<configuration->lods.distances[actualLOD-1]-5)
	{
		SetLOD(actualLOD - 1);
	}
	return true;
}

TerrainChunk::~TerrainChunk()
{
	for (int i = 0; i < configuration->lods.size;i++)
	{
		if (lods[i])
			delete lods[i];
	}
	delete lods;
	model = nullptr;
}



bool TerrainChunk::ActualizeLOD(glm::vec3 cameraPosition)
{
	return ActualiseVisiblity(cameraPosition);
}


void TerrainChunk::Initialize(glm::ivec2 position, PerlinNoise* noise,TerrainSystemConfiguration* configuration)
{
	this->position = position;
	this->noise = noise;
	lods = new Model*[configuration->lods.size];
	for (int i = 0; i < configuration->lods.size; i++)
		lods[i] = nullptr;
	color = glm::vec3(0.2f, 0.7f, 0.2f);
	actualLOD = -1;
	this->configuration = configuration;
}

glm::ivec2 TerrainChunk::GetPosition() const
{
	return position;
}

void TerrainChunk::Render(GLint modelLocation, GLint colorLocation) const
{
	if (!model)
		return;
	Renderable::Render(modelLocation, colorLocation);
}
