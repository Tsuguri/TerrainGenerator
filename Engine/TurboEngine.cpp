#include "TurboEngine.h"
#include <thread>
TurboEngine* TurboEngine::instance = NULL;


TurboEngine::TurboEngine()
{
	SetInstance(this);
}


TurboEngine::~TurboEngine()
{
	if (objectRenderer)
		delete objectRenderer;
}
int TurboEngine::Initialize(int width, int height, char* windowName, int maxFPS)
{
	if (maxFPS != -1)
		this->maxFrameTime = 1.0f / float(maxFPS);
	else
		this->maxFrameTime = -1.0f;
	//here goes glfw initialization
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	// Set the required callback functions
	glfwSetKeyCallback(window, KeyControl);
	glfwSetCursorPosCallback(window, MouseControl);
	glfwSetMouseButtonCallback(window, MouseButtonControl);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
	objectRenderer = new ForwardRenderer(width, height);
}

int TurboEngine::Run()
{
	double lastFrameTime = 0.0;
	int frameCounter = 0;
	double temp = 0.0;
	double time = 0.0;
	while (!glfwWindowShouldClose(window))
	{

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		frameCounter += 1;
		// Update timer 
			// TODO
		activeScene->Animate(lastFrameTime);

		// Render
		if (objectRenderer && activeScene)
			objectRenderer->Render(*activeScene);


		lastFrameTime = glfwGetTime() - temp;
		if (maxFrameTime != -1.0f && lastFrameTime < maxFrameTime)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(long(1000 * (maxFrameTime - lastFrameTime))));
			lastFrameTime = maxFrameTime;
		}
		time += lastFrameTime;
		if (time > 1.0)
		{
			std::cout << "FPS: " << frameCounter / time << std::endl;
			std::cout << "avg time: " << time / frameCounter << std::endl;
			time = 0.0;
			frameCounter = 0;
		}

		temp = glfwGetTime();
		glfwSwapBuffers(window);
		ResetMouse();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void TurboEngine::CloseWindow() const
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}

void TurboEngine::KeyControl(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (instance)
	{
		if (action == GLFW_PRESS)
			instance->OnButtonPress(key);
		if (action == GLFW_RELEASE)
			instance->OnButtonReleased(key);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && instance)
		instance->CloseWindow();
	//will be doing sth
}

void TurboEngine::MouseButtonControl(GLFWwindow* window, int button, int action, int mods)
{
	if (instance)
	{
		
		if (action == GLFW_PRESS)
			instance->OnMousePress(button);
		if (action == GLFW_RELEASE)
			instance->OnMouseRelease(button);
	}
}

void TurboEngine::MouseControl(GLFWwindow* window, double xpos, double ypos)
{
	if(instance)
	{
		instance->OnMouseMoved(xpos, ypos);
	}
}

void TurboEngine::OnMouseMoved(double xpos, double ypos)
{
	prevMousePos = actualMousePos;
	actualMousePos = glm::vec2(xpos, ypos);
	mouseDelta = actualMousePos - prevMousePos;
}

void TurboEngine::SetInstance(TurboEngine * engine)
{
	if (instance)
		throw "engine already exists!";
	instance = engine;
}

void TurboEngine::OnMousePress(int key)
{
	mouseButtonPressed[key] = true;
}

void TurboEngine::OnMouseRelease(int key)
{
	mouseButtonPressed[key] = false;
}

void TurboEngine::OnButtonReleased(int keyCode)
{
	keyPressed[keyCode] = false;
}

void TurboEngine::ResetMouse()
{
	mouseDelta = glm::vec2(0.0f);
}

void TurboEngine::OnButtonPress(int keyCode)
{
	keyPressed[keyCode] = true;
	std::cout << "Key pressed: " << keyCode << std::endl;
	switch (keyCode)
	{
	case GLFW_KEY_ESCAPE:
		instance->CloseWindow();
		break;
	}
}

void TurboEngine::SetScene(Scene* scene)
{
	activeScene = scene;
}

bool TurboEngine::IsButtonPressed(int keycode)
{
	return keyPressed[keycode];
}

bool TurboEngine::IsMouseButtonPressed(int keycode)
{
	if (keycode > 9 || keycode < 0)
		return false;
	return mouseButtonPressed[keycode];
}

glm::vec2 TurboEngine::GetMouseMove()
{
	return mouseDelta;
}

TurboEngine* TurboEngine::GetInstance()
{
	return instance;
}