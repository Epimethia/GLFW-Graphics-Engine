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

	void FixedTick();
	void Tick();
	void Render();

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
	
	static unsigned int m_WindowWidth;
	static unsigned int m_WindowHeight;
	static std::string m_WindowName;
	static class Input* m_pInputInstance;
	Shader* m_GlobalDefaultShader;

	double m_CurrentTime = 0.0;
	double m_PreviousTime = 0.0;
	double m_DeltaTime = 0.0;
	double m_TicksPerSecond = 1.0;
	double m_Timer = 0.0;
	unsigned int m_ElapsedFrames = 0;
	unsigned int m_UpdateTicks = 0;

	class Tetronimo* b0;
	class Tetronimo* b1;
	class Tetronimo* b2;
	class Tetronimo* b3;
	class Tetronimo* b4;
	class Tetronimo* b5;
	class Tetronimo* b6;

	class Sprite* BG;

	glm::mat4 m_VPMatrix;

public:

	//Setters and getters
	static unsigned int GetWindowHeight() { return m_WindowHeight; };
	static unsigned int GetWindowWidth() { return m_WindowWidth; };
	std::string GetWindowName() { return m_WindowName; };
	static void SetWindowHeight(unsigned int _Height) { m_WindowHeight = _Height; };
	static void SetWindowWidth(unsigned int _Width) { m_WindowWidth = _Width; };
	static void SetWindowName(std::string _WindowName) { m_WindowName = _WindowName; };
	Shader* GetGlobalDefaultShader() { return m_GlobalDefaultShader; };
	void SetTickRate(double _TicksPerSecond) { m_TicksPerSecond = _TicksPerSecond; };

};

