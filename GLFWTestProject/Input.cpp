#include "Input.h"
#include "Command.h"
#include "Tetronimo.h"

Input* Input::m_pInputInstance = nullptr;
Tetronimo* Input::ActiveTet = nullptr;
std::vector<class Tetronimo*> Input::TetVect;

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
	
	//if (!ActiveTet) return;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			it->Translate(1, 0);
		}
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			it->RotateLeft();
		}
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			it->RotateRight();
		}
	}
	
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			it->Translate(-1, 0);
		}
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			it->Translate(0, -1);
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		for (auto it : TetVect) {
			bool reachedBottom = true;
			while (reachedBottom) {
				reachedBottom = it->Translate(0, -1);
			}
		}
		
	}
}
