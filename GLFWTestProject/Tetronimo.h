#pragma once
#include <vector>
#include "Dependencies/GLM/glm.hpp"
#include "GameObjects.h"

enum class ETetronimoType {
	O_BLOCK = 0,
	T_BLOCK,
	I_BLOCK,
	J_BLOCK,
	L_BLOCK,
	S_BLOCK,
	Z_BLOCK
};

enum class ECurrentRotation {
	UP = 0,			//0 rotation
	RIGHT = 1,		//1 rotation
	DOWN = 2,		//2 rotation
	LEFT = 3		//3 rotation
};

class Tetronimo : public GameObject {

protected:
	std::vector<class Base_Block*> m_BlockVector;

	glm::mat4 m_VPMatrix = glm::mat4(1.0f);
	glm::vec2 m_BlockOriginPosition = { 50.0f, 50.0f };
	glm::vec2 m_BlockRotationOrigin = { 50.0f, 50.0f };
	glm::vec2 m_PerBlockOffset = { 0.0f, 0.0f };

	bool m_IsActive = false;

	void MoveTetToPersistenGrid();

	ETetronimoType m_TetronimoType = ETetronimoType::O_BLOCK;
	ECurrentRotation m_CurrentRotation = ECurrentRotation::UP;

public:
	Tetronimo();
	~Tetronimo();

	virtual void Init() override;
	virtual void Render() override;
	void RenderDebug();

	virtual void SetBlockPosition(glm::vec2 _Position);
	virtual void SetBlockGridPosition(int _X, int _Y);
	int GetBlockGridXPos() { return static_cast<int>(std::floor(m_BlockOriginPosition.x / TetronimoSpacing)); };
	int GetBlockGridYPos() { return static_cast<int>(std::floor(m_BlockOriginPosition.y / TetronimoSpacing)); };
	void SetIsActive(bool _IsActive) { m_IsActive = _IsActive; };
	bool GetIsActive() { return m_IsActive; };
	glm::vec2 GetPerBlockOffset() { return m_PerBlockOffset; };
	ETetronimoType GetTetronimoType() { return m_TetronimoType; };
	ECurrentRotation GetCurrentRotation() { return m_CurrentRotation; };

	std::vector<class Base_Block*>& GetBlockVector() { return m_BlockVector; };
	
	bool Translate(int _X, int _Y);

	static float TetronimoSpacing;
	static float TetronimoHalfSpacing;
};

