#pragma once
#include <vector>
#include "Dependencies/GLM/glm.hpp"

class Tetronimo {

protected:
	std::vector<class Base_Block*> m_BlockVector;

	glm::mat4 m_VPMatrix = glm::mat4(1.0f);
	glm::vec2 m_BlockOriginPosition = { 50.0f, 50.0f };
	glm::vec2 m_BlockRotationOrigin = { 50.0f, 50.0f };
	glm::vec2 m_PerBlockOffset = { 0.0f, 0.0f };

	bool m_IsActive = false;

	static float TetronimoSpacing;
	static float TetronimoHalfSpacing;

public:
	Tetronimo();
	~Tetronimo();

	virtual void Init() = 0;
	void Render();
	void RenderDebug();
	void Tick();

	void SetVPMatrix(glm::mat4 _VPMatrix) { m_VPMatrix = _VPMatrix; };
	virtual void SetBlockPosition(glm::vec2 _Position);
	virtual void SetBlockGridPosition(int _X, int _Y);
	int GetBlockGridXPos() { return static_cast<int>(std::floor(m_BlockOriginPosition.x / TetronimoSpacing)); };
	int GetBlockGridYPos() { return static_cast<int>(std::floor(m_BlockOriginPosition.y / TetronimoSpacing)); };
	void SetActive(bool _IsActive) { m_IsActive = _IsActive; };

	void RotateRight();
	void RotateLeft();
	bool Translate(int _X, int _Y);
};

