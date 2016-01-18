#include "ObjectRenderer.h"
#include "glew.h"
#include "wglew.h"
#include <glm/gtc/type_ptr.hpp>



void ObjectRenderer::Render(Camera* camera, Scene* scene)
{
	//glm::vec3 col = camera->GetGlobalPosition();
	glClearColor(0.2f, 0.33f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program->SetAsActive();
	GLint modelLocation = glGetUniformLocation(program->programId, "ModelMat");

	if (scene)
	{
		GLint lightLocation = glGetUniformLocation(program->programId, "lightType");
		glUniform1i(lightLocation, scene->lightningType);
		GLint lightDirLocation = glGetUniformLocation(program->programId, "lightDir");
		glUniform3fv(lightDirLocation, 1, glm::value_ptr(scene->LightDirection));
		GLint lightColorLocation = glGetUniformLocation(program->programId, "lightColor");
		glUniform3fv(lightColorLocation, 1, glm::value_ptr(scene->LightColor));

	}
	if (camera)
	{
		GLint viewLocation = glGetUniformLocation(program->programId, "ViewMat");
		GLint projectionLocation = glGetUniformLocation(program->programId, "ProjMat");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix(height / (float)width)));
		GLint cameraPosLocation = glGetUniformLocation(program->programId, "cameraPosition");
		glUniform3fv(cameraPosLocation, 1, glm::value_ptr(camera->GetGlobalPosition()));
	}

	for (auto i = 0; i < renderables.size(); i++)
	{
			renderables[i]->Render(modelLocation);
	}
}

void ObjectRenderer::Animate(float time)
{
	for (auto obj : renderables)
	{
		if (!obj->HasParent())
			obj->Animate(time);
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
	glPolygonMode(GL_BACK, GL_LINE);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
}

void ObjectRenderer::ResizeWindow(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	glViewport(0, 0, windowWidth, windowHeight);
}
