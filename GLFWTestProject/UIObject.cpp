#include "UIObject.h"
#include "Sprite.h"
#include "AssetLoader.h"
#include "Camera.h"

UIObject::UIObject() {
	m_Sprite = new Sprite();
}

UIObject::~UIObject() {

}

void UIObject::Init() {
	m_Sprite->SetShader(AssetLoader::ShaderMap.find("DEFAULT_SHADER")->second);
	m_Sprite->SetVPMatrix(Camera::GetVPMatrix());
	m_Sprite->SetTexture(AssetLoader::TextureMap.find(m_TextureName)->second);
	m_Sprite->Init();
}

void UIObject::Render() {
	m_Sprite->Render();
}

void UIObject::SetPosition(glm::vec2 _Position) {
	m_Position = _Position;
	m_Sprite->SetObjectPosition(m_Position);
}

void UIObject::SetSize(glm::vec2 _Size) {
	m_Sprite->SetObjectScale(_Size / 32.0f);
}

void UIObject::SetTextureImage(std::string _TextureName) {
	m_TextureName = _TextureName;
	m_Sprite->SetTexture(AssetLoader::TextureMap.find(m_TextureName)->second);
}
