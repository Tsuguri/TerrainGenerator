#ifndef RENDERABLEH
#define RENDERABLEH
#include <glm/glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Mesh.h"
#include "ShaderUtility.h"


class Renderable
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Mesh* mesh;
	ShaderProgram* shader;
	
public:
	Renderable(Mesh* mesh);
	void Render(GLint modelLocation);
};

#endif // !RENDERABLEH
