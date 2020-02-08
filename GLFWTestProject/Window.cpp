#include "Dependencies/GLEW/include/glew.h"

#include "Window.h"
#include "Input.h"

#include <random>
#include <iostream>
#include "Shader.h"
#include "DefaultShader.h"
#include "Blocks.h"
#include "AssetLoader.h"
#include "Sprite.h"

//Assigning static variables
Window* Window::m_pWindowInstance = nullptr;
GLFWwindow* Window::m_pWindowPtr = nullptr;
Input* Window::m_pInputInstance = nullptr;

//unsigned int Window::m_WindowWidth = 512;
//unsigned int Window::m_WindowHeight = 704;
unsigned int Window::m_WindowWidth = 1280;
unsigned int Window::m_WindowHeight = 768;
std::string Window::m_WindowName = "Default Window Name";

Window::Window() {
	m_GlobalDefaultShader = new Shader();
	glm::mat4 Projection = glm::ortho(0.0f, static_cast<float>(m_WindowWidth), 0.0f, static_cast<float>(m_WindowHeight), -1.0f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m_VPMatrix = Projection * View;
}

void Window::FixedTick() {
	b0->Tick();

	b1->Tick();
	b2->Tick();
	//b3->Tick();
	//b4->Tick();
	//b5->Tick();
	//b6->Tick();
}

void Window::Tick() {
	//Unfixed tick stuff
}

void Window::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	BG->Render();

	//Render here
	b0->Render();
	b1->Render();
	b2->Render();
	b3->Render();
	b4->Render();
	b5->Render();
	b6->Render();

	//b0->RenderDebug();
	//b1->RenderDebug();
	//b2->RenderDebug();
	//b3->RenderDebug();
	//b4->RenderDebug();
	//b5->RenderDebug();
	//b6->RenderDebug();

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
	if (!CreateWindow()) {
		return false;
	}
	InitInput();

	glfwSwapInterval(1);

	glewInit();

	//Creating Default shader
	m_GlobalDefaultShader->SetShaderName("Default Shader");
	m_GlobalDefaultShader->SetVertexShaderData(DefaultShaderData::VertexData);
	m_GlobalDefaultShader->SetFragmentShaderData(DefaultShaderData::FragmentData);
	m_GlobalDefaultShader->InitShader();

	AssetLoader::LoadTextures();
	b0 = new O_Block();
	b0->SetVPMatrix(m_VPMatrix);
	b0->Init();
	b0->SetActive(true);
	b0->SetBlockGridPosition(6, 20);
	//b0->SetBlockPosition(glm::vec2(160.0f));

	b1 = new I_Block();
	b1->SetVPMatrix(m_VPMatrix);
	b1->Init();
	b1->SetBlockGridPosition(6, 1);
	//b1->SetBlockPosition(glm::vec2(160.0f));
	b1->SetActive(true);

	b2 = new T_Block();
	b2->SetVPMatrix(m_VPMatrix);
	b2->Init();
	b2->SetBlockGridPosition(6, 1);
	b2->SetActive(true);

	b3 = new L_Block();
	b3->SetVPMatrix(m_VPMatrix);
	b3->Init();
	b3->SetBlockGridPosition(6, 6);

	b4 = new J_Block();
	b4->SetVPMatrix(m_VPMatrix);
	b4->Init();
	b4->SetBlockGridPosition(6, 6);

	b5 = new S_Block();
	b5->SetVPMatrix(m_VPMatrix);
	b5->Init();
	b5->SetBlockGridPosition(6, 10);

	b6 = new Z_Block();
	b6->SetVPMatrix(m_VPMatrix);
	b6->Init();
	b6->SetBlockGridPosition(6, 10);

	BG = new Sprite();
	BG->SetVPMatrix(m_VPMatrix);
	BG->SetTexture(AssetLoader::TextureMap.find("UI_BG_MAIN")->second);
	BG->SetShader(m_GlobalDefaultShader);
	BG->Init();
	BG->SetObjectScale(glm::vec2(40.0f, 24.0f));
	BG->SetObjectPosition(glm::vec2(0.0f));

	Input::ActiveTet = b0;
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

