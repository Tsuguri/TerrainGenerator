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
#include "Model.h"


class Renderable : public D3Component
{
private:
	glm::vec3 scale;
	Model* model;
	ShaderProgram* shader;
	
public:
	Renderable(Model* model);
	void Render(GLint modelLocation);
};

#endif // !RENDERABLEH
