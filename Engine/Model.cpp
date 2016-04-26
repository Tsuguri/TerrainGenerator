#include "Model.h"
#include <iostream>

Model::~Model()
{
	for(auto m : meshes)
	{
		delete m;
	}
}

Model::Model(char* path)
{

}

Model::Model(Mesh * mesh)
{
	meshes.push_back(mesh);
}

void Model::Render()
{
	for (auto mesh : meshes)
		mesh->Render();
}

