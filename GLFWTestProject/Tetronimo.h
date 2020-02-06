#pragma once
#include "Sprite.h"
#include <vector>
#include "Dependencies/GLM/glm.hpp"

class Tetronimo {

protected:
	std::vector<Sprite*> m_BlockVector;
	class Shader* m_ShaderProgram = nullptr;

	glm::mat4 m_VPMatrix = glm::mat4(1.0f);
	glm::vec2 m_BlockPosition = { 50.0f, 50.0f };

	bool m_IsActive = false;

public:
	Tetronimo();
	~Tetronimo();

	virtual void Init() = 0;
	void Render();
	void Tick();

	void SetVPMatrix(glm::mat4 _VPMatrix) { m_VPMatrix = _VPMatrix; };
	virtual void SetBlockPosition(glm::vec2 _Position);
	void SetActive(bool _IsActive) { m_IsActive = _IsActive; };
};

