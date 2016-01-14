#ifndef RENDERABLEH
#define RENDERABLEH

#include <glm/glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include "ShaderProgram.h"
#include "Vertex.h"


struct Renderable
{
private:
	glm::vec3 position;
	glm::quat rotation;
	ShaderProgram shader;
	
public:
	Renderable();
};

#endif // !RENDERABLEH
