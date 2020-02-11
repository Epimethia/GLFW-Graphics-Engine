#include "GameManager.h"
#include "Tetronimo.h"
#include "AssetLoader.h"
#include "Blocks.h"
#include "Base_Block.h"
#include "Dependencies/GLFW/include/glfw3.h"
#include "Scene.h"
#include <iostream>

void GameManager::FixedTick() {
	//If there is no active piece, generate one
	if (!m_ActivePiece) {
		m_ActivePiece = GenerateTetronimo();
	}
	
	//Translate the tetronimo downwards on tick
	TranslateActiveTet(0, -1);

}

void GameManager::Tick() {
	//Check if the piece is still active
	if (m_ActivePiece) {
		if (!m_ActivePiece->GetIsActive()) {
			for (auto it : m_ActivePiece->GetBlockVector()) {
				PlayGrid.push_back(it);
			}
			m_ActivePiece = nullptr;
		}
	}
}

void GameManager::RotateActiveTet(ERotationDirection _Direction) {
	switch (_Direction) {
		case ERotationDirection::CLOCKWISE:
			m_ActivePiece->RotateRight();
			break;
		case ERotationDirection::ANTI_CLOCKWISE:
			m_ActivePiece->RotateLeft();
			break;
		default: break;
	}
}

void GameManager::TranslateActiveTet(int _X, int _Y) {
	if (_X == 0) {
		if (CheckColliding(_X, _Y)) {
			m_ActivePiece->SetIsActive(false);
		}
		else {
			m_ActivePiece->Translate(_X, _Y);
		}
	}
	else {
		if (!CheckColliding(_X, _Y)) {
			m_ActivePiece->Translate(_X, _Y);
		}

	}

}

void GameManager::HardDropTet() {
	while (m_ActivePiece->GetIsActive()) {
		TranslateActiveTet(0, -1);
	}
	m_ActivePiece->SetIsActive(false);
}

void GameManager::ProcessInput(int _Key, int _Action, int _Mods) {
	if (!m_ActivePiece) return;

	//if (!ActiveTet) return;
	if (_Key == GLFW_KEY_LEFT && _Action == GLFW_PRESS) {
		TranslateActiveTet(-1, 0);
	}
	if (_Key == GLFW_KEY_RIGHT && _Action == GLFW_PRESS) {
		TranslateActiveTet(1, 0);
	}

	if (_Key == GLFW_KEY_Z && _Action == GLFW_PRESS) {
		RotateActiveTet(ERotationDirection::ANTI_CLOCKWISE);
	}

	if (_Key == GLFW_KEY_X && _Action == GLFW_PRESS) {
		RotateActiveTet(ERotationDirection::CLOCKWISE);
	}


	if (_Key == GLFW_KEY_DOWN && _Action == GLFW_PRESS) {
		TranslateActiveTet(0, -1);
	}

	if (_Key == GLFW_KEY_SPACE && _Action == GLFW_PRESS) {
		HardDropTet();
	}
}

Tetronimo* GameManager::GenerateTetronimo() {
	//Random Bag Generation

	if (m_RandomBag.size() == 0) {
		m_RandomBag.clear();
		//Populate a new bag of tetronimo blocks based on a random distribution
		std::vector<EBlockTypes> BlockBag = AssetLoader::GetRandomBagTemplate();
		while (BlockBag.size() > 0) {
			std::uniform_int_distribution<int> NewBagDistribution(0, static_cast<int>(BlockBag.size()) - 1);

			//clamping result
			int Result = std::max(0, std::min(NewBagDistribution(m_RandomGenerator), static_cast<int>(BlockBag.size())));

			EBlockTypes Type = BlockBag[Result];
			Tetronimo* t = nullptr;
			switch (Type) {
				case EBlockTypes::O_BLOCK:	t = new O_Block; break;
				case EBlockTypes::I_BLOCK:	t = new I_Block; break;
				case EBlockTypes::T_BLOCK:	t = new T_Block; break;
				case EBlockTypes::J_BLOCK:	t = new J_Block; break;
				case EBlockTypes::L_BLOCK:	t = new L_Block; break;
				case EBlockTypes::S_BLOCK:	t = new S_Block; break;
				case EBlockTypes::Z_BLOCK:	t = new Z_Block; break;
				default: break;
			}
			
			//Erase from the vector and push to the random bag
			BlockBag.erase(BlockBag.begin() + Result);
			t->Init();
			m_RandomBag.push_back(t);
		}
	}

	//Get tetronimo from the top of the bag and pop it off
	m_ActivePiece = m_RandomBag.back();
	m_ActivePiece->SetBlockGridPosition(6, 22);
	m_ActivePiece->SetIsActive(true);
	m_RandomBag.pop_back();

	m_ActiveScene->GetEntityVect().push_back(m_ActivePiece);
	return m_ActivePiece;
}

bool GameManager::CheckColliding(int _X, int _Y) {
	glm::vec2 Translation = { _X * Tetronimo::TetronimoSpacing, _Y * Tetronimo::TetronimoSpacing };

	for (auto GridIt : PlayGrid) {
		for (auto BlockIt : m_ActivePiece->GetBlockVector()) {

			glm::vec2 TranslatedPos = BlockIt->GetBlockTruePosition() + Translation;
			glm::vec2 GridBlockPos = GridIt->GetBlockTruePosition();
			glm::vec2 Difference = glm::abs(TranslatedPos - GridBlockPos);

			if (Difference.y < Tetronimo::TetronimoSpacing && Difference.x < Tetronimo::TetronimoSpacing) {
				return true;
			}
		}
	}
	return false;
}
