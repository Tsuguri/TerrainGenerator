#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <glm\glm.hpp>

#include "ObjectRenderer.h"



class TurboEngine
{
public:
	//(de)constructors
	TurboEngine();
	~TurboEngine();
	//methods
	int Initialize(int width, int height,char* windowName);
	int Run();
	void CloseWindow();

	//fields

private:
	//methods

	
	static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);

	void SetInstance(TurboEngine* engine);
	virtual void OnButtonPress(int keyCode);
	virtual void OnButtonReleased(int keyCode);
	//fields
	ObjectRenderer* objectRenderer;
	bool keyPressed[1024];
	GLFWwindow* window;
	static TurboEngine* instance;
};

