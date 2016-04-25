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
	int Initialize(int width, int height,char* windowName,int maxFPS=-1);
	int Run();
	void CloseWindow() const;
	void SetScene(Scene* scene);
	virtual bool IsButtonPressed(int keycode);
	virtual bool IsMouseButtonPressed(int keycode);
	virtual glm::vec2 GetMouseMove();

	static TurboEngine* GetInstance();
	//fields

private:
	//methods
	
	
	static void KeyControl(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseButtonControl(GLFWwindow* window, int button, int action, int mods);
	static void MouseControl(GLFWwindow* window, double xpos, double ypos);
	static void WindowResized(GLFWwindow* window, int width, int height);
	virtual void OnMouseMoved(double xpos, double ypos);
	virtual void OnWindowResize(int width, int height);
	static void SetInstance(TurboEngine* engine);

	virtual void OnMousePress(int key);
	virtual void OnMouseRelease(int key);
	virtual void OnButtonPress(int keyCode);
	virtual void OnButtonReleased(int keyCode);
	void ResetMouse();
	
	//fields
	Scene* activeScene;
	ForwardRenderer* objectRenderer;
	float maxFrameTime = -1.0f;
	glm::vec2 prevMousePos;
	glm::vec2 actualMousePos;
	glm::vec2 mouseDelta;
	
	bool keyPressed[1024];
	bool mouseButtonPressed[10];
	GLFWwindow* window;
	static TurboEngine* instance;

};

