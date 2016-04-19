#include "TurboEngine.h"

TurboEngine* TurboEngine::instance = NULL;


TurboEngine::TurboEngine()
{
	SetInstance(this);
}


TurboEngine::~TurboEngine()
{
}
int TurboEngine::Initialize(int width, int height, char* windowName)
{
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
	// Set the required callback functions
	glfwSetKeyCallback(window, KeyControl);

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

}

int TurboEngine::Run()
{
		float lastFrameTime=0;
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Update timer 
			// TODO
		//objectRenderer->Animate(lastFrameTime);

		// Render
		//TODO: setting up scene and camera.
		//objectRenderer->Render();
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void TurboEngine::CloseWindow()
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

void TurboEngine::SetInstance(TurboEngine * engine)
{
	if (instance)
		throw "engine already exists!";
	instance = engine;
}

void TurboEngine::OnButtonReleased(int keyCode)
{
	keyPressed[keyCode] = false;
}

void TurboEngine::OnButtonPress(int keyCode)
{
	keyPressed[keyCode] = true;
	switch (keyCode)
	{
	case GLFW_KEY_ESCAPE:
		instance->CloseWindow();
		break;
	}
}
