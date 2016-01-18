#ifndef RENDERABLEH
#define RENDERABLEH
#include <glm/glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Mesh.h"
#include "ShaderUtility.h"
#include "D3Component.h"
#include <vector>

class Renderable : public D3Component
{
private:
	glm::vec3 scale;
	Mesh* mesh;
	ShaderProgram* shader;

	
public:

	Renderable(Mesh* mesh);
	void Render(GLint modelLocation);
	void SetScale(glm::vec3 scale);
};

#endif // !RENDERABLEH
