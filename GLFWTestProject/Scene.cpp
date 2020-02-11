#include "Scene.h"
#include "Tetronimo.h"
#include "GameObjects.h"
#include "Blocks.h"
#include "UIObject.h"
#include "AssetLoader.h"
#include "Window.h"

#include "GameManager.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::Tick() {}

void Scene::FixedTick() {}

void Scene::Init() {
	//Creating the bg
	UIObject* BG = new UIObject();
	BG->SetPosition(glm::vec2(0.0f, 0.0f));
	BG->SetSize({ Window::GetWindowWidth(), Window::GetWindowHeight() });
	BG->SetTextureImage("UI_BG_MAIN");
	BG->Init();
	m_BackgroundUI.push_back(BG);
	BG = nullptr;
}



void Scene::Render() {
	for (auto it : m_BackgroundUI) {
		it->Render();
	}

	for (auto it : m_EntityVect) {
		it->Render();
	}

	for (auto it : m_ForegroundUI) {
		it->Render();
	}
}

