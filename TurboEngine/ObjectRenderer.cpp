#include "ObjectRenderer.h"
#include "glew.h"
#include "wglew.h"
#include <glm/gtc/type_ptr.hpp>


void ObjectRenderer::Render(Camera* camera)
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program->SetAsActive();
	GLint modelLocation = glGetUniformLocation(program->programId, "ModelMat");
	GLint viewLocation = glGetUniformLocation(program->programId, "ViewMat");
	GLint projectionLocation = glGetUniformLocation(program->programId, "ProjMat");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

	for (auto i = 0; i < renderables.size();i++)
	{
		renderables[i]->Render(modelLocation);
	}
}

void ObjectRenderer::AddRenderable(Renderable* renderable)
{

	renderables.push_back(renderable);
}

ObjectRenderer::ObjectRenderer(int windowWidth, int windowHeight, ShaderProgram* shader)
{
	program = shader;
	ResizeWindow(windowWidth, windowHeight);

	Initialization();
}

void ObjectRenderer::Initialization()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
}

void ObjectRenderer::ResizeWindow(int windowWidth, int windowHeight)
{
	glViewport(0, 0, windowWidth, windowHeight);
}
