#include "Blocks.h"
#include "Sprite.h"
#include "AssetLoader.h"
#include "Base_Block.h"


//------------------------------------------------------------------------------
//Helper function to create blocks and initialize the required variables. Helps
//reduce code duplication
//------------------------------------------------------------------------------
Base_Block* CreateBlock(glm::vec2 _BlockPosition, glm::vec2 _LocalOffset, std::string _TextureName) {
	Base_Block* g = new Base_Block();
	g->SetBlockPosition(_BlockPosition + _LocalOffset);
	g->SetLocalOffset(_LocalOffset);
	g->SetBlockTexture(_TextureName);
	g->Init();
	return g;
}

//------------------------------------------------------------------------------
//	[#][#]			Initializing O-Block structure
//	[#][#]
//------------------------------------------------------------------------------
void O_Block::Init() {
	Base_Block* g;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			g = CreateBlock(m_BlockOriginPosition, glm::vec2(j * TetronimoSpacing - TetronimoSpacing, i * TetronimoSpacing - TetronimoSpacing), "TEX_BRICK_YELLOW");
			m_BlockVector.push_back(g);
			g = nullptr;
		}
	}
}

void O_Block::SetBlockGridPosition(int _X, int _Y) {
	float x = static_cast<float>(_X) * TetronimoSpacing;
	float y = static_cast<float>(_Y) * TetronimoSpacing;

	SetBlockPosition(glm::vec2(x, y) + glm::vec2(TetronimoHalfSpacing));
}

//------------------------------------------------------------------------------
//	[#][#][#][#]	Initializing I-Block structure
//------------------------------------------------------------------------------
void I_Block::Init() {
	for (int i = 0; i < 4; i++) {
		Base_Block* g = CreateBlock(m_BlockOriginPosition, glm::vec2(i * TetronimoSpacing - (2.0f * TetronimoSpacing), 0.0f), "TEX_BRICK_CYAN");
		m_BlockVector.push_back(g);
		g = nullptr;
	}
}

void I_Block::SetBlockGridPosition(int _X, int _Y) {
	float x = static_cast<float>(_X) * TetronimoSpacing;
	float y = static_cast<float>(_Y) * TetronimoSpacing;

	SetBlockPosition(glm::vec2(x, y) + glm::vec2(TetronimoHalfSpacing));
}

//------------------------------------------------------------------------------
//	[#][#][#]		Initializing T-Block structure
//	   [#]
//------------------------------------------------------------------------------
void T_Block::Init() {
	Base_Block* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2((i * TetronimoSpacing) - (1.5f * TetronimoSpacing), -(0.5 * TetronimoSpacing)), "TEX_BRICK_PURPLE");
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2(TetronimoSpacing - (1.5f * TetronimoSpacing), (0.5 * TetronimoSpacing)), "TEX_BRICK_PURPLE");
	m_BlockVector.push_back(g);
	g = nullptr;
}

//------------------------------------------------------------------------------
//	      [#]		Initializing L-Block structure
//	[#][#][#]
//------------------------------------------------------------------------------
void L_Block::Init() {
	Base_Block* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2(i * TetronimoSpacing - (1.5f * TetronimoSpacing), -TetronimoHalfSpacing), "TEX_BRICK_ORANGE");
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2((TetronimoHalfSpacing), TetronimoHalfSpacing), "TEX_BRICK_ORANGE");
	g->m_Sprite->Init();
	g->m_Sprite->SetVPMatrix(m_VPMatrix);
	m_BlockVector.push_back(g);
	g = nullptr;

}

//------------------------------------------------------------------------------
//	[#]				Initializing J-Block structure
//	[#][#][#]
//------------------------------------------------------------------------------
void J_Block::Init() {
	Base_Block* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2(i * TetronimoSpacing - (1.5f * TetronimoSpacing), -TetronimoHalfSpacing), "TEX_BRICK_BLUE");
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2(-(1.5f * TetronimoSpacing), TetronimoHalfSpacing), "TEX_BRICK_BLUE");
	m_BlockVector.push_back(g);
	g = nullptr;
}

//------------------------------------------------------------------------------
//	   [#][#]		Initializing S-Block structure
//	[#][#]
//------------------------------------------------------------------------------
void S_Block::Init() {
	float SBlockOffset = 0.0f;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			Base_Block* g = CreateBlock(m_BlockOriginPosition, glm::vec2((j * TetronimoSpacing) - (1.5f * TetronimoSpacing) + SBlockOffset, i * TetronimoSpacing - TetronimoHalfSpacing), "TEX_BRICK_GREEN");
			m_BlockVector.push_back(g);
			g = nullptr;
		}
		SBlockOffset = TetronimoSpacing;
	}
}

//------------------------------------------------------------------------------
//	[#][#]			Initializing S-Block structure
//	   [#][#]
//------------------------------------------------------------------------------
void Z_Block::Init() {
	float ZBlockOffset = TetronimoSpacing;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			Base_Block* g = CreateBlock(m_BlockOriginPosition, glm::vec2((j * TetronimoSpacing) - (1.5f * TetronimoSpacing) + ZBlockOffset, i * TetronimoSpacing - TetronimoHalfSpacing), "TEX_BRICK_RED");
			m_BlockVector.push_back(g);
			g = nullptr;
		}
		ZBlockOffset = 0.0f;
	}
}
