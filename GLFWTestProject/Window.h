#pragma once
#include <string>
#include "Shader.h"
#include "Dependencies/GLFW/include/glfw3.h"

#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"

//Class that handles the window setup and functionality

class Window {

	//Singleton Instance Methods
private:

	//Method overloads. This prevents the unwanted construction,
	//destruction. Also overloads creation via assignment and copying.
	Window();
	~Window() {};
	Window(const Window&);
	Window& operator=(const Window&);

	static Window* m_pWindowInstance;

public:

	static Window* GetInstance();
	static void DestroyInstance();

	bool InitGLFW();
	void Loop();

	//GLFW Methods
private:

	static struct GLFWwindow* m_pWindowPtr;

	GLFWwindow* CreateWindow();
	void InitInput();
	void DestroyWindow();

	static void GLFWErrorCallback(int error, const char* description);
	//static void GLFW
	
	unsigned int m_WindowWidth = 640;
	unsigned int m_WindowHeight = 480;
	std::string m_WindowName = "Default Window Name";
	static class Input* m_pInputInstance;
	Shader* m_GlobalDefaultShader;

	class GameObject* g;

	glm::mat4 m_VPMatrix;

public:

	//Setters and getters
	unsigned int GetWindowHeight() { return m_WindowHeight; };
	unsigned int GetWindowWidth() { return m_WindowWidth; };
	std::string GetWindowName() { return m_WindowName; };
	void SetWindowHeight(unsigned int _Height) { m_WindowHeight = _Height; };
	void SetWindowWidth(unsigned int _Width) { m_WindowWidth = _Width; };
	void SetWindowName(std::string _WindowName) { m_WindowName = _WindowName; };

};

