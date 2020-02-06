#include "Blocks.h"
#include "Sprite.h"
#include "AssetLoader.h"

float spacing = 32.0f;

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
			g = CreateBlock(m_BlockPosition, glm::vec2(j * spacing, i * spacing), "TEX_BRICK_YELLOW");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
			m_BlockVector.push_back(g);
			g = nullptr;
		}
	}
}

//------------------------------------------------------------------------------
//	[#][#][#][#]	Initializing I-Block structure
//------------------------------------------------------------------------------
void I_Block::Init() {
	for (int i = 0; i < 4; i++) {
		Sprite* g = CreateBlock(m_BlockPosition, glm::vec2(0.0f, i * spacing), "TEX_BRICK_CYAN");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}
}

//------------------------------------------------------------------------------
//	[#][#][#]		Initializing T-Block structure
//	   [#]
//------------------------------------------------------------------------------
void T_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockPosition, glm::vec2(i * spacing, 0.0f), "TEX_BRICK_PURPLE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockPosition, glm::vec2(spacing, spacing), "TEX_BRICK_PURPLE");
	g->SetShader(m_ShaderProgram);
	g->Init();
	g->SetVPMatrix(m_VPMatrix);
	m_BlockVector.push_back(g);
	g = nullptr;
}

//------------------------------------------------------------------------------
//	[#][#][#]		Initializing L-Block structure
//	      [#]
//------------------------------------------------------------------------------
void L_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockPosition, glm::vec2(i * spacing, spacing), "TEX_BRICK_ORANGE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockPosition, glm::vec2(0.0f, 0.0f), "TEX_BRICK_ORANGE");
	g->SetShader(m_ShaderProgram);
	g->Init();
	g->SetVPMatrix(m_VPMatrix);
	m_BlockVector.push_back(g);
	g = nullptr;

}

//------------------------------------------------------------------------------
//	[#][#][#]		Initializing J-Block structure
//	[#]
//------------------------------------------------------------------------------
void J_Block::Init() {
	Sprite* g;
	for (int i = 0; i < 3; i++) {
		g = CreateBlock(m_BlockPosition, glm::vec2(i * spacing, spacing), "TEX_BRICK_BLUE");
		g->SetShader(m_ShaderProgram);
		g->Init();
		g->SetVPMatrix(m_VPMatrix);
		m_BlockVector.push_back(g);
		g = nullptr;
	}

	g = CreateBlock(m_BlockPosition, glm::vec2(2.0f * spacing, 0.0f), "TEX_BRICK_BLUE");
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
			Sprite* g = CreateBlock(m_BlockPosition, glm::vec2((j * spacing) + SBlockOffset, i * spacing), "TEX_BRICK_GREEN");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
			m_BlockVector.push_back(g);
			g = nullptr;
		}
		SBlockOffset = spacing;
	}
}

//------------------------------------------------------------------------------
//	[#][#]			Initializing S-Block structure
//	   [#][#]
//------------------------------------------------------------------------------
void Z_Block::Init() {
	float ZBlockOffset = spacing;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			Sprite* g = CreateBlock(m_BlockPosition, glm::vec2((j * spacing) + ZBlockOffset, i * spacing), "TEX_BRICK_RED");
			g->SetShader(m_ShaderProgram);
			g->Init();
			g->SetVPMatrix(m_VPMatrix);
			m_BlockVector.push_back(g);
			g = nullptr;
		}
		ZBlockOffset = 0.0f;
	}
}
