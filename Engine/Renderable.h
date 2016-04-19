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
#include "Model.h"

class Renderable : public D3Component
{
private:
	glm::vec3 scale;
	Model* model;
	ShaderProgram* shader;

	
public:
	glm::vec3 color;
	Renderable();
	Renderable(Model* mesh);
	virtual void Render(GLint modelLocation, GLint colorLocation) const;
	void SetScale(glm::vec3 scale);
};

#endif // !RENDERABLEH
