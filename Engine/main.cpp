#define _CRT_SECURE_NO_DEPRECATE
#include "TurboEngine.h"
#include "ShaderProgram.h"
#include "InputControlAnimation.h"
#include "TerrainSystem.h"
#include "LodInfo.h"
#include "TextRenderer.h"
#include "RangefinderSystem.h"

Renderable* CreateRend2();

inline bool FileExists(const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	std::cout<<"file "<<name<<" not found"<<std::endl;
		return false;
}

//Generates default LodInfo
LodInfo GenerateLodInfo()
{
	LodInfo lod;
	lod.distances.push_back(40);
	lod.sizes.push_back(50);
	lod.distances.push_back(100);
	lod.sizes.push_back(25);
	lod.distances.push_back(200);
	lod.sizes.push_back(5);
	lod.size = 3;
	return lod;
}

//Generates default terrain configuration - change if want to start with different setup
TerrainSystemConfiguration GenerateConfiguration()
{
	TerrainSystemConfiguration conf;
	conf.lods = GenerateLodInfo();
	conf.seed = 12553;
	conf.amplitude = 30;
	conf.frequency = 300.0f;
	conf.chunkSize = glm::vec2(20);
	return conf;
}

int main(int argc, char** argv)
{
	// Checking if files are present
	if (!FileExists("fonts/arial.ttf")  || !FileExists("BasicVertex.vsh") || !FileExists("BasicFragment.fsh") || !FileExists("FontVertex.vsh") ||!FileExists("FontFragment.fsh"))
		return -1;

	// First step: creation&initialization of Engine 
	TurboEngine engine;
	engine.Initialize(1920, 1080, "Projekt indywidualny - generator terenu");

	//Loads base shaders.
	ShaderProgram* shad = new ShaderProgram("BasicVertex.vsh", "BasicFragment.fsh");
	//Sets initial camera.
	Camera* camera = new Camera(glm::vec3(0, 10, -4), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 0.1f, 200.0f, 45);
	// Sets move controller.
	auto anim = new InputControlAnimation();
	camera->SetAnimation(anim);
	anim->StartAnimation();
	//initialize scene and adds modules to engine.
	Scene* sc = new Scene(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f), camera);
	sc->shader = shad;
	engine.SetScene(sc);
	sc->AddAnimatable(camera);

	//Creation of terrain system
	auto terrain = new TerrainSystem(GenerateConfiguration());
	terrain->Seed(50, 120, 200);
	//Creation of rangefind system (highly useless)
	auto rangefind = new RangefinderSystem();
	
	// Adding both modules to engine
	engine.AddModule(rangefind);
	engine.AddModule(terrain);
	
	// Game loop
	return engine.Run();
}


