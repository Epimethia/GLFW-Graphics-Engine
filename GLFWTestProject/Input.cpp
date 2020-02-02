#include "Input.h"
#include "Command.h"

Input* Input::m_pInputInstance = nullptr;

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
	}
	
	//Passing the curre
}
