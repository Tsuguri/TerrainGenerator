#include "ObjectRenderer.h"
#include "glew.h"
#include "wglew.h"

void ObjectRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
}

ObjectRenderer::ObjectRenderer(int windowWidth, int windowHeight, int amount)
{
	count = 0; size = 8;
	objects = new Renderable[8];
	ResizeWindow(windowWidth, windowHeight);

	Initialization();
}

void ObjectRenderer::Initialization()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void ObjectRenderer::ResizeWindow(int windowWidth, int windowHeight)
{
	glViewport(0, 0, windowWidth, windowHeight);
}
