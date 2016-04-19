#include "ObjectRenderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL\glew.h>



void ForwardRenderer::Render(const Scene& scene)
{
	//glm::vec3 col = camera->GetGlobalPosition();
	glClearColor(0.2f, 0.33f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.shader->SetAsActive();
	GLint modelLocation = glGetUniformLocation(scene.shader->programId, "ModelMat");
	GLint colorLocation = glGetUniformLocation(scene.shader->programId, "defaultColor");


	GLint lightDirLocation = glGetUniformLocation(scene.shader->programId, "lightDir");
	glUniform3fv(lightDirLocation, 1, glm::value_ptr(scene.LightDirection));
	GLint lightColorLocation = glGetUniformLocation(scene.shader->programId, "lightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(scene.LightColor));

	if (scene.activeCamera)
	{
		GLint viewLocation = glGetUniformLocation(scene.shader->programId, "ViewMat");
		GLint projectionLocation = glGetUniformLocation(scene.shader->programId, "ProjMat");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(scene.activeCamera->GetViewMatrix()));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(scene.activeCamera->GetProjectionMatrix(height / (float)width)));
		GLint cameraPosLocation = glGetUniformLocation(scene.shader->programId, "cameraPosition");
		glUniform3fv(cameraPosLocation, 1, glm::value_ptr(scene.activeCamera->GetGlobalPosition()));
	}

	for(auto obj : scene.renderables)
	{
		RenderObject(*obj,modelLocation,colorLocation);
	}
}




ForwardRenderer::ForwardRenderer(int windowWidth, int windowHeight) 
{
	ResizeWindow(windowWidth, windowHeight);

	Initialization();
}

void ForwardRenderer::Initialization()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void ForwardRenderer::RenderObject(const Renderable& object,int modelLocation,int colorLocation) const
{
	
	object.Render(modelLocation,colorLocation);
}

void ForwardRenderer::ResizeWindow(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	glViewport(0, 0, windowWidth, windowHeight);
}
