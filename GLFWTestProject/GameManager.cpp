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

	bool IsColliding = CheckRotation(_Direction);
	std::cout << "IsColliding: " << IsColliding << std::endl;
	if (IsColliding == true) {
		return;
	}

	switch (_Direction) {
		case ERotationDirection::CLOCKWISE:

			for (auto BlockIt : m_ActivePiece->GetBlockVector()) {
				glm::vec2 BlockOffset = m_ActivePiece->GetPerBlockOffset();
				float TranslatedX = BlockIt->GetLocalOffset().x + BlockOffset.x;
				float TranslatedY = BlockIt->GetLocalOffset().y + BlockOffset.y;

				BlockIt->SetLocalOffset({ TranslatedY - BlockOffset.x, -TranslatedX - BlockOffset.y });
			}

			break;
		case ERotationDirection::ANTI_CLOCKWISE:

			for (auto BlockIt : m_ActivePiece->GetBlockVector()) {
				glm::vec2 BlockOffset = m_ActivePiece->GetPerBlockOffset();
				float TranslatedX = BlockIt->GetLocalOffset().x + BlockOffset.x;
				float TranslatedY = BlockIt->GetLocalOffset().y + BlockOffset.y;

				BlockIt->SetLocalOffset({ -TranslatedY - BlockOffset.x, TranslatedX - BlockOffset.y });
			}

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
				return true; // if colliding
			}
		}
	}
	return false;
}

bool GameManager::CheckColliding(int _X, int _Y, std::vector<Base_Block*> _BlockVect) {
	glm::vec2 Translation = { _X * Tetronimo::TetronimoSpacing, _Y * Tetronimo::TetronimoSpacing };

	for (auto GridIt : PlayGrid) {
		for (auto BlockIt : _BlockVect) {

			glm::vec2 TranslatedPos = BlockIt->GetBlockTruePosition() + Translation;
			glm::vec2 GridBlockPos = GridIt->GetBlockTruePosition();
			glm::vec2 Difference = glm::abs(TranslatedPos - GridBlockPos);

			if (Difference.y < Tetronimo::TetronimoSpacing && Difference.x < Tetronimo::TetronimoSpacing) {
				return true; // if colliding
			}
		}
	}
	return false;
}

bool GameManager::CheckRotation(ERotationDirection _Direction) {
	system("CLS");

	std::vector<Base_Block> TempBlockVect;
	for (auto TempBlockIt : m_ActivePiece->GetBlockVector()) {
		TempBlockVect.push_back(*TempBlockIt);
	}

	glm::vec2 BlockOffset = m_ActivePiece->GetPerBlockOffset();

	//Rotate the temp block vector
	switch (_Direction) {

		case ERotationDirection::CLOCKWISE: {

			for (auto BlockIt : TempBlockVect) {
				float TranslatedX = BlockIt.GetLocalOffset().x + BlockOffset.x;
				float TranslatedY = BlockIt.GetLocalOffset().y + BlockOffset.y;

				BlockIt.SetLocalOffset({ TranslatedY - BlockOffset.x, -TranslatedX - BlockOffset.y });
			}

			break;
		}

		case ERotationDirection::ANTI_CLOCKWISE: {

			for (auto BlockIt : TempBlockVect) {
				float TranslatedX = BlockIt.GetLocalOffset().x + BlockOffset.x;
				float TranslatedY = BlockIt.GetLocalOffset().y + BlockOffset.y;

				BlockIt.SetLocalOffset({ -TranslatedY - BlockOffset.x, TranslatedX - BlockOffset.y });
			}

			break;
		}

		default: break;
	}



	//Check if the block is colliding with anything
	glm::vec2 BottomLeftBounds = { Tetronimo::TetronimoSpacing * 15, Tetronimo::TetronimoSpacing * 2 };
	glm::vec2 TopRightBounds = { Tetronimo::TetronimoSpacing * 24, Tetronimo::TetronimoSpacing * 11 };

	for (auto BlockIt : TempBlockVect) {
		glm::vec2 BlockPosition = BlockIt.GetBlockTruePosition();

		std::cout << "Block Position: {" << (BlockPosition.x - BottomLeftBounds.x) / Tetronimo::TetronimoSpacing << "," << (BlockPosition.y - BottomLeftBounds.y) / Tetronimo::TetronimoSpacing << "} | ";

		//Left Right Check
		if ((BlockPosition.x < BottomLeftBounds.x) || (BlockPosition.x > TopRightBounds.x)) {
			std::cout << "Colliding x: " << BlockPosition.x - BottomLeftBounds.x << std::endl;
			return true;
		};

		if (BlockPosition.y < BottomLeftBounds.y) {
			std::cout << "Colliding y: " << BlockPosition.y - BottomLeftBounds.y << std::endl;
			return true;
		}
		std::cout << std::endl;
	}

	std::cout << "Not Colliding\n";
	//int DesiredRotationIndex = static_cast<int>(m_ActivePiece->GetCurrentRotation()) + 1;
	//if (DesiredRotationIndex > 3) DesiredRotationIndex = 0;
	//ECurrentRotation DesiredRotationEnum = static_cast<ECurrentRotation>(DesiredRotationIndex);

	//std::vector<std::pair<int, int>> CurrentWallKickData;

	//if (m_ActivePiece->GetTetronimoType() == ETetronimoType::I_BLOCK) {
	//	switch (DesiredRotationEnum) {
	//		case ECurrentRotation::RIGHT:
	//			CurrentWallKickData = AssetLoader::WallKickDataMap.find("IBLOCK_UP_TO_RIGHT")->second;
	//			break;
	//		case ECurrentRotation::DOWN:
	//			CurrentWallKickData = AssetLoader::WallKickDataMap.find("IBLOCK_RIGHT_TO_DOWN")->second;
	//			break;
	//		case ECurrentRotation::LEFT:
	//			CurrentWallKickData = AssetLoader::WallKickDataMap.find("IBLOCK_DOWN_TO_LEFT")->second;
	//			break;
	//		case ECurrentRotation::UP:
	//			CurrentWallKickData = AssetLoader::WallKickDataMap.find("IBLOCK_LEFT_TO_UP")->second;
	//			break;
	//		default: break;
	//	}

	//	int CurrentWallKickCheck = 0;
	//	bool RotationFailed = true;

	//	while (RotationFailed == true) {
	//		int WallKickXOffset = CurrentWallKickData[CurrentWallKickCheck].first;
	//		int WallKickYOffset = CurrentWallKickData[CurrentWallKickCheck].second;

	//		RotationFailed = CheckColliding(WallKickXOffset, WallKickYOffset, TempBlockVect);

	//		CurrentWallKickCheck++;

	//		//If the current loop has gone through all 
	//		if (CurrentWallKickCheck > 4) RotationFailed = false;
	//		if (RotationFailed == false) break;
	//	};

	//	return RotationFailed;
	//}
	//m_ActivePiece->GetBlockVector() = TempBlockVect;

	return false;
}
