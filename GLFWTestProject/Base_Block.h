#pragma once
#include "Dependencies/GLM/glm.hpp"
#include <string>
#include "GameObjects.h"

class Base_Block : public GameObject {
public:
	Base_Block();
	~Base_Block() {};
	class Sprite* m_Sprite = nullptr;

	virtual void Init() override;
	virtual void Render() override;

	void SetBlockPosition(glm::vec2 _Position);
	glm::vec2 GetBlockPosition() { return m_BlockPosition; };
	glm::vec2 GetBlockTruePosition() { return m_BlockPosition + m_LocalOffset; };
	void SetLocalOffset(glm::vec2 _LocalOffset);
	glm::vec2 GetLocalOffset() { return m_LocalOffset; };
	void SetBlockTexture(std::string _TextureName);

private:
	glm::vec2 m_BlockPosition = { 0.0f, 0.0f };
	glm::vec2 m_LocalOffset = { 0.0f, 0.0f };
	std::string m_TextureName = "";
};

