#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <glm\glm.hpp>



class TurboEngine
{
public:
	TurboEngine();
	~TurboEngine();
	int Initialize(int width, int height,char* windowName);
	int Run();
	void CloseWindow();

private:
	static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);
	GLFWwindow* window;
	static TurboEngine* instance;
	void SetInstance(TurboEngine* engine);
};

