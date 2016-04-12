#include "TurboEngine.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char* argv)
{
	TurboEngine engine;
	engine.Initialize(800,600,"Projekt indywidualny - generator terenu");

	// Game loop
	return engine.Run();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}