#include "TurboEngine.h"
#include "ShaderProgram.h"
#include "CurveAnimation.h"
#include "TerrainSystem.h"
#include "LodInfo.h"

Renderable* CreateRend2();

LodInfo GenerateLodInfo()
{
	LodInfo lod;
	lod.distances.push_back(50);
	lod.sizes.push_back(100);
	lod.distances.push_back(120);
	lod.sizes.push_back(50);
	lod.distances.push_back(200);
	lod.sizes.push_back(20);
	lod.size = 3;
	return lod;
}

TerrainSystemConfiguration GenerateConfiguration()
{
	TerrainSystemConfiguration conf;
	conf.lods = GenerateLodInfo();
	conf.seed = 12553;
	conf.amplitude = 8;

	return conf;
}

int main(int argc, char** argv)
{

	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}
	TurboEngine engine;
	// Engine initialization
	engine.Initialize(800, 600, "Projekt indywidualny - generator terenu");

	//Loads base shaders.
	ShaderProgram* shad = new ShaderProgram("BasicVertex.vsh", "BasicFragment.fsh");
	//Sets initial camera.
	Camera* camera = new Camera(glm::vec3(0, 10, -4), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 0.1f, 200.0f, 45);

	auto terrain = new TerrainSystem(GenerateConfiguration());
	terrain->Seed(12352, 50, 120, 200, glm::vec2(20));
	// Sets move controller.
	auto anim = new InputControlAnimation();
	camera->SetAnimation(anim);
	anim->StartAnimation();
	//initialize scene and adds modules to engine.
	Scene* sc = new Scene(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f), camera);
	sc->shader = shad;
	engine.SetScene(sc);
	engine.AddModule(terrain);
	sc->AddAnimatable(camera);
	//test model
	Renderable* rend = CreateRend2();
	sc->AddRenderable(rend);

	// Game loop
	return engine.Run();
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