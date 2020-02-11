#include "Input.h"
#include "Command.h"
#include "Tetronimo.h"
#include "GameManager.h"

Input* Input::m_pInputInstance = nullptr;
GameManager* Input::m_ActiveGameManager = nullptr;

Input* Input::GetInstance() {
	if (!m_pInputInstance) {
		m_pInputInstance = new Input();
	}
	return m_pInputInstance;
}

void Input::DestroyInstance() {
	delete m_pInputInstance;
	m_pInputInstance = nullptr;
}

void Input::BindInput(int _Key, int _Action, Command* _Command) {
	
}

void Input::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}

	m_ActiveGameManager->ProcessInput(key, action, mods);
}
