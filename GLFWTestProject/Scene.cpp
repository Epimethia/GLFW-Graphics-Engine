#include "Scene.h"
#include "Tetronimo.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::Tick() {

}

void Scene::FixedTick() {
	//If there is an active piece, translate it down
	if (!m_ActivePiece) {
		m_ActivePiece = GenerateTetronimo();
	}
	m_ActivePiece->Translate(0, -1);

}

void Scene::Render() {}

void Scene::ProcessInput() {}

Tetronimo* Scene::GenerateTetronimo() {
	return nullptr;
}
