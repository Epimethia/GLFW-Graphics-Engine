#include "Tetronimo.h"
#include "Sprite.h"
#include "Window.h"
#include "Shader.h"
#include "Dependencies/GLFW/include/glfw3.h"
#include <iostream>



float Tetronimo::TetronimoSpacing = 32.0f;
float Tetronimo::TetronimoHalfSpacing = Tetronimo::TetronimoSpacing / 2.0f;

std::string DebugVec2(glm::vec2 _Vec) {
	std::string str;
	
	str += std::to_string(_Vec.x);
	str += "|";
	str += std::to_string(_Vec.y);
	return str;
}

Tetronimo::Tetronimo() {
	m_ShaderProgram = Window::GetInstance()->GetGlobalDefaultShader();
}

Tetronimo::~Tetronimo() {}

void Tetronimo::Render() {
	for (auto BlockIt : m_BlockVector) {
		BlockIt->Render();
	}
}

void Tetronimo::RenderDebug() {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glm::vec2 WindowDimensions = glm::vec2(static_cast<float>(Window::GetWindowWidth()), static_cast<float>(Window::GetWindowHeight())) / 2.0f;

	for (auto BlockIt : m_BlockVector) {
		glm::vec4 OriginPos = glm::vec4((BlockIt->GetObjectPosition()) / WindowDimensions, 1.0f, 1.0f);
		glm::vec4 OffsetPos = glm::vec4((BlockIt->GetObjectPosition() + BlockIt->GetLocalOffset() + glm::vec2(TetronimoHalfSpacing)) / WindowDimensions, 1.0f, 1.0f);

		glVertex3f(OriginPos.x - 1.0f, OriginPos.y - 1.0f, 0.9f);
		glVertex3f(OffsetPos.x - 1.0f, OffsetPos.y - 1.0f, 0.9f);
	}

	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);

	//red = rotation origin
	glColor3f(1.0f, 0.1f, 0.5f);
	glVertex3f(m_BlockRotationOrigin.x / WindowDimensions.x - 1.0f, m_BlockRotationOrigin.y / WindowDimensions.y - 1.0f, 0.9f);

	//green = origin
	glColor3f(0.5f, 1.0f, 0.1f);
	glVertex3f(m_BlockOriginPosition.x / WindowDimensions.x - 1.0f, m_BlockOriginPosition.y / WindowDimensions.y - 1.0f, 0.9f);
	glEnd();

}

void Tetronimo::Tick() {
	if (m_IsActive) {
		SetBlockGridPosition(GetBlockGridXPos(), GetBlockGridYPos());
	}
}

void Tetronimo::SetBlockPosition(glm::vec2 _Position) {
	m_BlockOriginPosition = _Position;
	m_BlockRotationOrigin = _Position + m_PerBlockOffset;
	glm::vec2 GridOffset = glm::vec2(TetronimoSpacing * 14.0f, TetronimoSpacing);

	for (auto BlockIt : m_BlockVector) {
		BlockIt->SetObjectPosition(m_BlockRotationOrigin + GridOffset);
	}
}

void Tetronimo::SetBlockGridPosition(int _X, int _Y) {
	float x = static_cast<float>(_X) * TetronimoSpacing;
	float y = static_cast<float>(_Y) * TetronimoSpacing;

	SetBlockPosition(glm::vec2(x, y));
}

void Tetronimo::RotateRight() {
	SetBlockGridPosition(GetBlockGridXPos() + 1, GetBlockGridYPos());
	std::cout << GetBlockGridXPos() << std::endl;
}

void Tetronimo::RotateLeft() {
	SetBlockGridPosition(GetBlockGridXPos() - 1, GetBlockGridYPos());
}

bool Tetronimo::Translate(int _X, int _Y) {
	//Do collision checks here
	//Out of bounds
	if (GetBlockGridXPos() + _X < 1) return false;
	if (GetBlockGridXPos() + _X > 10) return false;
	if (GetBlockGridYPos() + _Y < 1) return false;

	//if successful, move the block
	SetBlockGridPosition(GetBlockGridXPos() + _X, GetBlockGridYPos() + _Y);
	std::cout << GetBlockGridXPos() << "|" << GetBlockGridYPos() << std::endl;
	return true;
}