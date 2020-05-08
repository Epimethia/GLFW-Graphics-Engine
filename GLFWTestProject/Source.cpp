//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup ")
#include "Dependencies/GLFW/include/glfw3.h"

#include "Window.h"

int main() {

	if (!Window::GetInstance()->InitGLFW()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	Window::GetInstance()->Loop();

	return 0;
}