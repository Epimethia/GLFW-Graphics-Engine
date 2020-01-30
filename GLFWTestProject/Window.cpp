#include "Window.h"
#include "Input.h"

#include <random>

//Assigning static variables
Window* Window::m_pWindowInstance = nullptr;
GLFWwindow* Window::m_pWindowPtr = nullptr;
Input* Window::m_pInputInstance = nullptr;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 10);

float Random() {
	return static_cast<float>(distribution(generator)) / 10.0f;
}

//------------------------------------------------------------
//Creates an instance of the window if none has been created.
//Returns a pointer to the reference if otherwise.
//------------------------------------------------------------
Window* Window::GetInstance() {
	if (!m_pWindowInstance) {
		m_pWindowInstance = new Window();
	}
	return m_pWindowInstance;
}

//------------------------------------------------------------
//Destroys the instance if there is one, and reassigns it to 
//null, allowing another instance to be created.
//------------------------------------------------------------
void Window::DestroyInstance() {
	delete m_pWindowInstance;
	m_pWindowInstance = nullptr;
}

//------------------------------------------------------------
//Inits GLFW and binds any required functionality
//------------------------------------------------------------
bool Window::InitGLFW() {
	if (!glfwInit()) {
		return false;
	}

	glfwSetErrorCallback(GLFWErrorCallback);

	//Creating the window and setting OpenGL context to the created window
	if (!CreateWindow()) {
		return false;
	}

	InitInput();

	glfwSwapInterval(1);
	return true;
}

//------------------------------------------------------------
//The main rendering loop. This loops until the window is given
//the signal to close (glfwWindowShouldClose returns true)
//------------------------------------------------------------
void Window::Loop() {
	while (!glfwWindowShouldClose(m_pWindowPtr)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(Random(), Random(), Random(), Random());


		//Render here


		glfwSwapBuffers(m_pWindowPtr);
		glfwPollEvents();
	}
	DestroyWindow();
}

//------------------------------------------------------------
//Initializes and creates the GLFW window. Returns a window 
//reference on successful creation.
//------------------------------------------------------------
GLFWwindow* Window::CreateWindow() {
	//If there is already a window created, destroy it and create another
	if (m_pWindowPtr) DestroyWindow();
	m_pWindowPtr = nullptr;

	//Creating the window 
	m_pWindowPtr = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName.c_str(), NULL, NULL);
	if (m_pWindowPtr) {
		glfwMakeContextCurrent(m_pWindowPtr);
	}
	return m_pWindowPtr;
	
}

//------------------------------------------------------------
//Initializes the input handler and binds the relevant functions
//to the callback.
//------------------------------------------------------------
void Window::InitInput() {
	m_pInputInstance = Input::GetInstance();
	glfwSetKeyCallback(m_pWindowPtr, &m_pInputInstance->InputCallback);
}

//------------------------------------------------------------
//Calls GLFW to destroy the window context and terminates the
//program, exiting.
//------------------------------------------------------------
void Window::DestroyWindow() {
	glfwDestroyWindow(m_pWindowPtr);
	m_pWindowPtr = nullptr;
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//------------------------------------------------------------
//------------------------------------------------------------
void Window::GLFWErrorCallback(int error, const char* description) {
	//todo: error callback
}

