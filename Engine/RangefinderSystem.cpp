#include "RangefinderSystem.h"
#include "TextRenderer.h"
#include <sstream>
#include <iomanip>

RangefinderSystem* RangefinderSystem::instance = NULL;
RangefinderSystem* RangefinderSystem::Get()
{
	return instance;
}

RangefinderSystem::RangefinderSystem()
{
	scene = nullptr;
	instance = this;
}

void RangefinderSystem::Update(float time)
{
	if (working)
	{
		auto position = scene->activeCamera->GetGlobalPosition();
		int i = 0;
		for (auto obj : objects)
		{

			std::ostringstream stream;
			auto p = glm::length(position - obj->GetGlobalPosition());
			stream << "Obiekt " << i << ": "<<std::fixed<<std::setprecision(1) << p;
			TextRenderer::Get()->RenderText(stream.str(), 25.0f, 10.0f + i*40.0f, 1.0f, glm::vec3(0.0f));
			i++;
		}
	}
}

void RangefinderSystem::Initialize(TurboEngine* engine)
{
	scene = engine->GetCurrentScene();
}

void RangefinderSystem::EndWork()
{
	for (auto obj : objects)
	{
		scene->RemoveRenderable(obj);
		delete obj;
	}
	objects.clear();
}
Renderable* CreateRend2()
{
	std::vector<Vertex>* vecs = new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();

	vecs->push_back(Vertex(1, 1, 1, 1, 0, 0, 1, 0));//1
	vecs->push_back(Vertex(1, 1, -1, 1, 0, 0, 1, 0));//1
	vecs->push_back(Vertex(1, -1, 1, 1, 0, 0, 1, 0));//1
	vecs->push_back(Vertex(1, -1, -1, 1, 0, 0, 1, 0));//1

	indices->push_back(0);
	indices->push_back(3);
	indices->push_back(1);
	indices->push_back(0);//1
	indices->push_back(2);//1
	indices->push_back(3);//1

	vecs->push_back(Vertex(-1, 1, 1, -1, 0, 0, 1, 0));//4
	vecs->push_back(Vertex(-1, 1, -1, -1, 0, 0, 1, 0));//4
	vecs->push_back(Vertex(-1, -1, 1, -1, 0, 0, 1, 0));//4
	vecs->push_back(Vertex(-1, -1, -1, -1, 0, 0, 1, 0));//4

	indices->push_back(4);
	indices->push_back(5);
	indices->push_back(7);
	indices->push_back(4);//1
	indices->push_back(7);//1
	indices->push_back(6);//1

	vecs->push_back(Vertex(1, 1, 1, 0, 1, 0, 1, 0));//2
	vecs->push_back(Vertex(1, 1, -1, 0, 1, 0, 1, 0));//2
	vecs->push_back(Vertex(-1, 1, 1, 0, 1, 0, 1, 0));//2
	vecs->push_back(Vertex(-1, 1, -1, 0, 1, 0, 1, 0));//2

	indices->push_back(8);
	indices->push_back(9);
	indices->push_back(11);
	indices->push_back(8);//1
	indices->push_back(11);//1
	indices->push_back(10);//1

	vecs->push_back(Vertex(1, -1, 1, 0, -1, 0, 1, 0));//5
	vecs->push_back(Vertex(1, -1, -1, 0, -1, 0, 1, 0));//5
	vecs->push_back(Vertex(-1, -1, 1, 0, -1, 0, 1, 0));//5
	vecs->push_back(Vertex(-1, -1, -1, 0, -1, 0, 1, 0));//5

	indices->push_back(12);
	indices->push_back(15);
	indices->push_back(13);
	indices->push_back(15);//1
	indices->push_back(12);//1
	indices->push_back(14);//1

	vecs->push_back(Vertex(1, 1, 1, 0, 0, 1, 1, 0));//
	vecs->push_back(Vertex(1, -1, 1, 0, 0, 1, 1, 0));//
	vecs->push_back(Vertex(-1, 1, 1, 0, 0, 1, 1, 0));
	vecs->push_back(Vertex(-1, -1, 1, 0, 0, 1, 1, 0));

	indices->push_back(16);
	indices->push_back(19);
	indices->push_back(17);
	indices->push_back(16);//1
	indices->push_back(18);//1
	indices->push_back(19);//1

	vecs->push_back(Vertex(1, 1, -1, 0, 0, -1, 1, 0));
	vecs->push_back(Vertex(1, -1, -1, 0, 0, -1, 1, 0));
	vecs->push_back(Vertex(-1, 1, -1, 0, 0, -1, 1, 0));
	vecs->push_back(Vertex(-1, -1, -1, 0, 0, -1, 1, 0));

	indices->push_back(20);
	indices->push_back(21);
	indices->push_back(23);
	indices->push_back(20);//1
	indices->push_back(23);//1
	indices->push_back(22);//1

	Renderable* rend = new Renderable(new Model(new Mesh(*vecs, *indices)));
	rend->color = glm::vec3(0.2f, 0.2f, 0.2f);
	return rend;
}
void RangefinderSystem::StartWorking(std::vector<glm::vec3> positions)
{
	working = true;
	for (auto pos : positions)
	{
		auto p = CreateRend2();
		p->SetLocalPosition(pos);
		scene->AddRenderable(p);
		objects.push_back(p);
	}
}
