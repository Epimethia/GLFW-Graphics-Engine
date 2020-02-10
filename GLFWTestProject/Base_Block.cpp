#include "Base_Block.h"
#include "Sprite.h"
#include "AssetLoader.h"
#include "Camera.h"

Base_Block::Base_Block() {
	m_Sprite = new Sprite();
}

void Base_Block::Init() {
	m_Sprite->SetShader(AssetLoader::ShaderMap.find("DEFAULT_SHADER")->second);
	m_Sprite->SetVPMatrix(Camera::GetVPMatrix());
	m_Sprite->SetTexture(AssetLoader::TextureMap.find(m_TextureName)->second);
	m_Sprite->Init();
}

void Base_Block::Render() {
	m_Sprite->Render();
}

void Base_Block::SetBlockPosition(glm::vec2 _Position) {
	m_BlockPosition = _Position;
	m_Sprite->SetObjectPosition(m_BlockPosition);
}

void Base_Block::SetLocalOffset(glm::vec2 _Offset) {
	m_LocalOffset = _Offset;
	m_Sprite->SetLocalOffset(m_LocalOffset);
}

void Base_Block::SetBlockTexture(std::string _TextureName) {
	m_TextureName = _TextureName;
}
