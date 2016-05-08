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



void TerrainChunk::CreateLOD1()
{
	if (lod1)
		return;
	lod1 = CreateLOD(100);
}

void TerrainChunk::CreateLOD2()
{
	if (lod2)
		return;
	lod2 = CreateLOD(25);
}

void TerrainChunk::CreateLOD3()
{
	if (lod3)
		return;
	lod3 = CreateLOD(5);
}

void TerrainChunk::SetLOD(int lod)
{
	switch (lod)
	{
	case 1:
		CreateLOD1();
		model = lod1;
		break;
	case 2:
		CreateLOD2();
		model = lod2;
		break;
	case 3:
		CreateLOD3();
		model = lod3;
		break;
	}
	actualLOD = lod;
}

Model* TerrainChunk::CreateLOD(int size) const
{
	float fre = 100;//frequency
	float ts = this->size.x / (float)size;
	float ampl = 10;
	float** heights = new float*[size+1];
	for (int i = 0; i < size + 1;i++)
	{
		heights[i] = new float[size + 1];
		for (int j = 0; j < size + 1; j++)
			heights[i][j] = GetHeight((position.x + i*ts) / fre, (position.y + ts*j) / fre) * ampl;
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
	//return noise->noise(x, y, 0) + noise->noise(20 * x, 20 * y, 0);
	return static_cast<float>(noise->noise(8 * x, 8 * y, 0) + noise->noise(4 * x, 4 * y, 0)*0.5f + noise->noise(2 * x, 2 * y, 0)*0.25f);
}

bool TerrainChunk::ActualiseVisiblity(glm::vec3 cameraPosition)
{
	glm::vec2 temp = (position + size / 2);
	float distance = glm::length(cameraPosition - glm::vec3(temp.x, 0.0f, temp.y));
	switch (actualLOD)
	{
	case 1:
		if (distance > TerrainSystem::LODDistance1 + 5)
		{
			SetLOD(2);
		}
		break;
	case 2:
		if (distance > TerrainSystem::LODDistance2 + 5)
		{
			SetLOD(3);
		}
		if (distance < TerrainSystem::LODDistance1 - 5)
		{
			SetLOD(1);
		}
		break;
	case 3:
		if (distance < TerrainSystem::LODDistance2 - 5)
		{
			SetLOD(2);
		}
		else if (distance>TerrainSystem::LODDistance3+20)
			return false;
		break;
	default:
		if (distance < TerrainSystem::LODDistance1)
		{
			CreateLOD1();
			actualLOD = 1;
			model = lod1;
		}
		else if (distance < TerrainSystem::LODDistance2)
		{
			CreateLOD2();
			actualLOD = 2;
			model = lod2;
		}
		else if (distance < TerrainSystem::LODDistance3)
		{
			CreateLOD3();
			actualLOD = 3;
			model = lod3;
		}
		else if(distance > TerrainSystem::LODDistance3+20)
			return false;
		break;
	}
	return true;

}

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



bool TerrainChunk::ActualizeLOD(glm::vec3 cameraPosition, glm::vec2 direction)
{
	return ActualiseVisiblity(cameraPosition);
}


void TerrainChunk::Initialize(glm::ivec2 position, glm::ivec2 size, PerlinNoise* noise)
{
	this->position = position;
	this->size = size;
	this->noise = noise;
	lod1 = lod2 = lod3 = nullptr;
	color = glm::vec3(0.2f, 0.7f, 0.2f);
	actualLOD = -1;
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
