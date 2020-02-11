#include <iostream>

#include "Dependencies/GLEW/include/glew.h"
#include "Window.h"

#include "Input.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Scene.h"
#include "GameManager.h"

//Assigning static variables
Window* Window::m_pWindowInstance = nullptr;
GLFWwindow* Window::m_pWindowPtr = nullptr;
Input* Window::m_pInputInstance = nullptr;

unsigned int Window::m_WindowWidth = 1280;
unsigned int Window::m_WindowHeight = 768;
std::string Window::m_WindowName = "Default Window Name";

Window::Window() {
	Camera::InitCamera();
	m_ActiveScene = new Scene();
	m_ActiveGameManager = new GameManager();
}

void Window::FixedTick() {
	m_ActiveGameManager->FixedTick();
	m_ActiveScene->FixedTick();
}

void Window::Tick() {
	m_ActiveGameManager->Tick();
	m_ActiveScene->Tick();
}

void Window::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//Render Here
	m_ActiveScene->Render();

	glfwSwapBuffers(m_pWindowPtr);
	glfwPollEvents();
}

//------------------------------------------------------------------------------
//Creates an instance of the window if none has been created.
//Returns a pointer to the reference if otherwise.
//------------------------------------------------------------------------------
Window* Window::GetInstance() {
	if (!m_pWindowInstance) {
		m_pWindowInstance = new Window();
	}
	return m_pWindowInstance;
}

//------------------------------------------------------------------------------
//Destroys the instance if there is one, and reassigns it to 
//null, allowing another instance to be created.
//------------------------------------------------------------------------------
void Window::DestroyInstance() {
	delete m_pWindowInstance;
	m_pWindowInstance = nullptr;
}

//------------------------------------------------------------------------------
//Inits GLFW and binds any required functionality
//------------------------------------------------------------------------------
bool Window::InitGLFW() {

	if (!glfwInit()) {
		return false;
	}

	glfwSetErrorCallback(GLFWErrorCallback);

	//Creating the window and setting OpenGL context to the created window
	if (!CreateWindow()) return false;


	glfwSwapInterval(1);
	glewInit();

	InitInput();

	Input::SetActiveGameManager(m_ActiveGameManager);
	m_ActiveGameManager->SetActiveScene(m_ActiveScene);

	AssetLoader::LoadAssets();

	m_ActiveScene->Init();

	return true;
}

//------------------------------------------------------------------------------
//The main rendering loop. This loops until the window is given
//the signal to close (glfwWindowShouldClose returns true)
//------------------------------------------------------------------------------
void Window::Loop() {
	while (!glfwWindowShouldClose(m_pWindowPtr)) {

		//Fixed Time loop processing
		m_CurrentTime = glfwGetTime();
		m_DeltaTime += (m_CurrentTime - m_PreviousTime) / (1.0 / m_TicksPerSecond);
		m_PreviousTime = m_CurrentTime;

		while (m_DeltaTime >= 1.0) {

			FixedTick();
			m_DeltaTime -= 1.0;
			m_UpdateTicks++;

		}
		Tick();
		m_ElapsedFrames++;

		////Print FPS/
		//if (glfwGetTime() - m_Timer > 1.0) {
		//	m_Timer = glfwGetTime();
		//	std::cout << "FPS: " << m_ElapsedFrames << " Updates:" << m_UpdateTicks << std::endl;
		//	m_UpdateTicks = 0, m_ElapsedFrames = 0;
		//}

		Render();

	}
	DestroyWindow();
}

//------------------------------------------------------------------------------
//Initializes and creates the GLFW window. Returns a window 
//reference on successful creation.
//------------------------------------------------------------------------------
GLFWwindow* Window::CreateWindow() {
	//If there is already a window created, destroy it and create another
	if (m_pWindowPtr) DestroyWindow();
	m_pWindowPtr = nullptr;

	//Creating the window 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_pWindowPtr = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName.c_str(), NULL, NULL);
	if (m_pWindowPtr) {
		glfwMakeContextCurrent(m_pWindowPtr);
		glfwSetWindowPos(m_pWindowPtr, 25, 25);
	}
	return m_pWindowPtr;
	
}

//------------------------------------------------------------------------------
//Initializes the input handler and binds the relevant functions
//to the callback.
//------------------------------------------------------------------------------
void Window::InitInput() {
	m_pInputInstance = Input::GetInstance();
	glfwSetKeyCallback(m_pWindowPtr, &m_pInputInstance->InputCallback);
}

//------------------------------------------------------------------------------
//Calls GLFW to destroy the window context and terminates the
//program, exiting.
//------------------------------------------------------------------------------
void Window::DestroyWindow() {
	glfwDestroyWindow(m_pWindowPtr);
	m_pWindowPtr = nullptr;
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Window::GLFWErrorCallback(int error, const char* description) {
	//todo: error callback
}

