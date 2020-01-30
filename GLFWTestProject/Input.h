#pragma once
#include "Dependencies/GLFW/include/glfw3.h"
#include "Command.h"
#include <map>


struct Key {
	int KeyName;
	int KeyAction;
	Command* Command;
};

class Input {

	//Singleton Instance Methods
private:

	Input() {};
	~Input() {};
	Input(const Input&);
	Input& operator=(const Input&);

	static Input* m_pInputInstance;
	//Keybind map for <<key, action>, command>
	static Key KeybindArray[10];

public:

	static Input* GetInstance();
	static void DestroyInstance();
	static void BindInput(int _Key, int _Action, Command* _Command);

	static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

