#include "Tetronimo.h"
#include "Window.h"
#include "Shader.h"



Tetronimo::Tetronimo() {
	m_ShaderProgram = Window::GetInstance()->GetGlobalDefaultShader();
}

Tetronimo::~Tetronimo() {}

void Tetronimo::Render() {
	for (auto BlockIt : m_BlockVector) {
		BlockIt->Render();
	}
}

void Tetronimo::Tick() {
	if (m_IsActive) {
		SetBlockPosition(m_BlockPosition + glm::vec2(0.0f, -50.0f));
	}
}

void Tetronimo::SetBlockPosition(glm::vec2 _Position) {
	m_BlockPosition = _Position;
	for (auto BlockIt : m_BlockVector) {
		BlockIt->SetObjectPosition(_Position);
	}
}

