#include "Blocks.h"
#include "Sprite.h"
#include "AssetLoader.h"


//------------------------------------------------------------------------------
//Helper function to create blocks and initialize the required variables. Helps
//reduce code duplication
//------------------------------------------------------------------------------
Sprite* CreateBlock(glm::vec2 _BlockPosition, glm::vec2 _LocalOffset, std::string _TextureName) {
	Sprite* g = new Sprite();
	g->SetObjectPosition(_BlockPosition);
	g->SetLocalOffset(_LocalOffset);
	g->SetTexture(AssetLoader::TextureMap.find(_TextureName)->second);
	return g;
}

//------------------------------------------------------------------------------
//	[#][#]			Initializing O-Block structure
//	[#][#]
//------------------------------------------------------------------------------
void O_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			g = CreateBlock(m_BlockOriginPosition, glm::vec2(j * TetronimoSpacing - (TetronimoSpacing), i * TetronimoSpacing - (TetronimoSpacing)), "TEX_BRICK_YELLOW");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
			m_BlockVector.push_back(g);
			g = nullptr;
		}
	}
}
//
//void O_Block::SetBlockPosition(glm::vec2 _Position) {
//	m_BlockPosition = _Position + m_PerBlockOffset;
//	m_BlockPosition = _Position - glm::vec2(TetronimoSpacing);
//
//	for (auto BlockIt : m_BlockVector) {
//		BlockIt->SetObjectPosition(m_BlockPosition);
//	}
//}
//
//void O_Block::SetBlockGridPosition(unsigned int _X, unsigned int _Y) {
//	glm::vec2 InitialOffset( TetronimoSpacing);
//
//	float XPos = static_cast<float>(_X) * TetronimoSpacing;
//	float YPos = static_cast<float>(_Y) * TetronimoSpacing;
//
//	m_BlockPosition = 2.0f * InitialOffset + glm::vec2(XPos, YPos);
//	m_BlockPosition = glm::vec2(XPos, YPos) + InitialOffset;
//	for (auto BlockIt : m_BlockVector) {
//		BlockIt->SetObjectPosition(m_BlockPosition);
//	}
//}

//------------------------------------------------------------------------------
//	[#][#][#][#]	Initializing I-Block structure
//------------------------------------------------------------------------------
void I_Block::Init() {
	for (int i = 0; i < 4; i++) {
		Sprite* g = CreateBlock(m_BlockOriginPosition, glm::vec2(0.0f, i * TetronimoSpacing - (2.0f * TetronimoSpacing)), "TEX_BRICK_CYAN");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}
}

//void I_Block::SetBlockPosition(glm::vec2 _Position) {
//	m_BlockPosition = _Position + m_PerBlockOffset;
//	m_BlockPosition = _Position;
//
//	for (auto BlockIt : m_BlockVector) {
//		BlockIt->SetObjectPosition(m_BlockPosition);
//	}
//}
//
//void I_Block::SetBlockGridPosition(unsigned int _X, unsigned int _Y) {
//	glm::vec2 InitialOffset(TetronimoSpacing, 2.0f * TetronimoSpacing);
//
//	float XPos = static_cast<float>(_X) * TetronimoSpacing;
//	float YPos = static_cast<float>(_Y) * TetronimoSpacing;
//
//	m_BlockPosition = InitialOffset + glm::vec2(XPos, YPos);
//	m_BlockPosition = glm::vec2(XPos, YPos - (2.0f * TetronimoSpacing)) + InitialOffset;
//	for (auto BlockIt : m_BlockVector) {
//		BlockIt->SetObjectPosition(m_BlockPosition);
//	}
//}


//------------------------------------------------------------------------------
//	[#][#][#]		Initializing T-Block structure
//	   [#]
//------------------------------------------------------------------------------
void T_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2((i * TetronimoSpacing) - (1.5f * TetronimoSpacing), -(0.5 * TetronimoSpacing)), "TEX_BRICK_PURPLE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2(TetronimoSpacing - (1.5f * TetronimoSpacing), (0.5 * TetronimoSpacing)), "TEX_BRICK_PURPLE");
	g->SetShader(m_ShaderProgram);
	g->Init();
	g->SetVPMatrix(m_VPMatrix);
	m_BlockVector.push_back(g);
	g = nullptr;
}

//------------------------------------------------------------------------------
//	      [#]		Initializing L-Block structure
//	[#][#][#]
//------------------------------------------------------------------------------
void L_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2(i * TetronimoSpacing - (1.5f * TetronimoSpacing), -TetronimoHalfSpacing), "TEX_BRICK_ORANGE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2((TetronimoHalfSpacing), TetronimoHalfSpacing), "TEX_BRICK_ORANGE");
	g->SetShader(m_ShaderProgram);
	g->Init();
	g->SetVPMatrix(m_VPMatrix);
	m_BlockVector.push_back(g);
	g = nullptr;

}

//------------------------------------------------------------------------------
//	[#]				Initializing J-Block structure
//	[#][#][#]
//------------------------------------------------------------------------------
void J_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockOriginPosition, glm::vec2(i * TetronimoSpacing - (1.5f * TetronimoSpacing), -TetronimoHalfSpacing), "TEX_BRICK_BLUE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockOriginPosition, glm::vec2(-(1.5f * TetronimoSpacing), TetronimoHalfSpacing), "TEX_BRICK_BLUE");
	g->SetShader(m_ShaderProgram);
	g->Init();
	g->SetVPMatrix(m_VPMatrix);
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
			Sprite* g = CreateBlock(m_BlockOriginPosition, glm::vec2((j * TetronimoSpacing) - (1.5f * TetronimoSpacing) + SBlockOffset, i * TetronimoSpacing - TetronimoHalfSpacing), "TEX_BRICK_GREEN");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
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
			Sprite* g = CreateBlock(m_BlockOriginPosition, glm::vec2((j * TetronimoSpacing) - (1.5f * TetronimoSpacing) + ZBlockOffset, i * TetronimoSpacing - TetronimoHalfSpacing), "TEX_BRICK_RED");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
			m_BlockVector.push_back(g);
			g = nullptr;
		}
		ZBlockOffset = 0.0f;
	}
}
