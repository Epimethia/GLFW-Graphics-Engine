#pragma once
#include "GameObjects.h"
#include "Dependencies/GLM/glm.hpp"
#include <string>

class UIObject : public GameObject {
public:
	UIObject();
	~UIObject();

	virtual void Init() override;
	virtual void Render() override;

	void SetPosition(glm::vec2 _Position);
	glm::vec2 GetPosition() { return m_Position; };
	void SetSize(glm::vec2 _Size);

	void SetTextureImage(std::string _TextureName);

private:
	glm::vec2 m_Position = { 0.0f, 0.0f };
	class Sprite* m_Sprite = nullptr;
	std::string m_TextureName = "";

};
