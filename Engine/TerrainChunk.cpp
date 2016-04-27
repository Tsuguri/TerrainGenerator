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

	int size = 100;
	int count = size - 1;
	Quad** quads = new Quad*[count];
	for (int i = 0; i < count; i++)
		quads[i] = new Quad[count];

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			Quad temp = quads[i][j];
			noise->noise(position.x + i, position.y + j, 0);
			temp.up.one.position = glm::vec3(position.x + i, GetHeight((position.x + i) / size, (position.y + j) / size), position.y + j);
			temp.up.two.position = glm::vec3(position.x + i + 1, noise->noise((position.x + i + 1) / size, (position.y + j) / size, 0), position.y + j);
			temp.up.three.position = glm::vec3(position.x + i + 1, noise->noise((position.x + i + 1) / size, (position.y + j + 1) / size, 0), position.y + j + 1);

			temp.down.one.position = glm::vec3(position.x + i, noise->noise((position.x + i) / size, (position.y + j) / size, 0), position.y + j);
			temp.down.two.position = glm::vec3(position.x + i, noise->noise((position.x + i) / size, (position.y + j + 1) / size, 0), position.y + j + 1);
			temp.down.three.position = glm::vec3(position.x + i + 1, noise->noise((position.x + i + 1) / size, (position.y + j + 1) / size, 0), position.y + j + 1);

			quads[i][j] = temp;
		}
	}


	//generacja normalnych


	std::vector<Vertex>* vecs = new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();
	//przesyłanie
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
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
	//vecs->push_back(Vertex(-20, 0, -20, 0, 1, 0, 1, 0));
	//vecs->push_back(Vertex(-20, 0, 120, 0, 1, 0, 1, 0));
	//vecs->push_back(Vertex(100, 0, 120, 0, 1, 0, 1, 0));
	//vecs->push_back(Vertex(100, 0, -20, 0, 1, 0, 1, 0));
	//indices->push_back(0);
	//indices->push_back(1);
	//indices->push_back(2);
	//indices->push_back(0);
	//indices->push_back(2);
	//indices->push_back(3);

	lod1 = new Model(new Mesh(*vecs, *indices));
	model = lod1;

	for (int i = 0; i < count; i++)
		delete quads[i];
	delete quads;
	delete vecs;
	delete indices;
}

float TerrainChunk::GetHeight(float x, float y)
{
	return (float)noise->noise(x, y, 0);
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

void TerrainChunk::Initialize(glm::vec2 position, glm::vec2 size, PerlinNoise* noise)
{
	this->position = position;
	this->size = size;
	this->noise = noise;
	lod1 = lod2 = lod3 = nullptr;
	CreateLOD1();
}
