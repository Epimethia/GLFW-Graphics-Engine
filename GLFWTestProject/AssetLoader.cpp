#include "AssetLoader.h"

#include "Dependencies/SOIL/include/SOIL.h"
#include "Dependencies/GLFW/include/glfw3.h"
#include "Shader.h"
#include "DefaultShader.h"
#include <iostream>

std::map<std::string, GLuint> AssetLoader::TextureMap;
std::map<std::string, Shader*> AssetLoader::ShaderMap;
std::vector<EBlockTypes> AssetLoader::RandomBagTemplateVect;
std::map<std::string, std::vector<std::pair<int, int>>> AssetLoader::WallKickDataMap;

void AssetLoader::LoadAssets() {
	//std::string DefaultPath = "";
	//Load brick texture
	TextureMap.insert(LoadTexture("TEX_BRICK_BLUE","Assets/Textures/Brick Textures/blue.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_GREEN","Assets/Textures/Brick Textures/green.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_YELLOW","Assets/Textures/Brick Textures/yellow.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_PURPLE","Assets/Textures/Brick Textures/purple.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_ORANGE","Assets/Textures/Brick Textures/orange.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_RED","Assets/Textures/Brick Textures/red.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_CYAN","Assets/Textures/Brick Textures/cyan.png"));
	TextureMap.insert(LoadTexture("TEX_BRICK_GRAY","Assets/Textures/Brick Textures/gray.png"));
	TextureMap.insert(LoadTexture("UI_BG_MAIN","Assets/Textures/UI/background.png"));

	ShaderMap.insert(LoadShader("DEFAULT_SHADER", DefaultShaderData::VertexData, DefaultShaderData::FragmentData));

	RandomBagTemplateVect = {
		EBlockTypes::O_BLOCK,
		EBlockTypes::I_BLOCK,
		EBlockTypes::T_BLOCK,
		EBlockTypes::J_BLOCK,
		EBlockTypes::L_BLOCK,
		EBlockTypes::S_BLOCK,
		EBlockTypes::Z_BLOCK
	};

	//standard block wall kick data
	std::vector<std::pair<int, int>> UpToRightWallKickData = { {0, 0}, {-1, 0}, {-1, 1}, {0,-2}, {-1,-2}};
	std::vector<std::pair<int, int>> RightToUpWallKickData = { {0, 0}, {1, 0}, {1,-1}, {0, 2}, {1, 2}};
	std::vector<std::pair<int, int>> RightToDownWallKickData = { {0, 0}, {1, 0}, {1,-1}, {0, 2}, {1, 2}};
	std::vector<std::pair<int, int>> DownToRightWallKickData = { {0, 0}, {-1, 0}, {-1, 1}, {0,-2}, {-1,-2}};
	std::vector<std::pair<int, int>> DownToLeftWallKickData = { {0, 0}, {1, 0}, {1, 1}, {0,-2}, {1,-2}};
	std::vector<std::pair<int, int>> LeftToDownWallKickData = { {0, 0},	{-1, 0}, {-1,-1}, {0, 2}, {-1, 2}};
	std::vector<std::pair<int, int>> LeftToUpWallKickData = { {0, 0}, {-1, 0}, {-1,-1}, {0, 2}, {-1, 2}};
	std::vector<std::pair<int, int>> UpToLeftWallKickData = { {0, 0}, {1, 0}, {1, 1}, {0,-2}, {1,-2}};
	
	//I Block Wall Kick Data
	std::vector<std::pair<int, int>> IBlockUpToRightWallKickData = { {0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2} };
	std::vector<std::pair<int, int>> IBlockRightToUpWallKickData = { {0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2} };
	std::vector<std::pair<int, int>> IBlockRightToDownWallKickData = { {0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1} };
	std::vector<std::pair<int, int>> IBlockDownToRightWallKickData = { {0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1} };
	std::vector<std::pair<int, int>> IBlockDownToLeftWallKickData = { {0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2} };
	std::vector<std::pair<int, int>> IBlockLeftToDownWallKickData = { {0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2} };
	std::vector<std::pair<int, int>> IBlockLeftToUpWallKickData = { {0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1} };
	std::vector<std::pair<int, int>> IBlockUpToLeftWallKickData = { {0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1} };

	WallKickDataMap.insert(std::make_pair("UP_TO_RIGHT", UpToRightWallKickData));
	WallKickDataMap.insert(std::make_pair("RIGHT_TO_UP", RightToUpWallKickData));
	WallKickDataMap.insert(std::make_pair("RIGHT_TO_DOWN", RightToDownWallKickData));
	WallKickDataMap.insert(std::make_pair("DOWN_TO_RIGHT", DownToRightWallKickData));
	WallKickDataMap.insert(std::make_pair("DOWN_TO_LEFT", DownToLeftWallKickData));
	WallKickDataMap.insert(std::make_pair("LEFT_TO_DOWN", LeftToDownWallKickData));
	WallKickDataMap.insert(std::make_pair("LEFT_TO_UP", LeftToUpWallKickData));
	WallKickDataMap.insert(std::make_pair("UP_TO_LEFT", UpToLeftWallKickData));

	WallKickDataMap.insert(std::make_pair("IBLOCK_UP_TO_RIGHT", IBlockUpToRightWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_RIGHT_TO_UP", IBlockRightToUpWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_DOWN_TO_RIGHT", IBlockDownToRightWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_RIGHT_TO_DOWN", IBlockRightToDownWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_DOWN_TO_LEFT", IBlockDownToLeftWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_LEFT_TO_DOWN", IBlockLeftToDownWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_LEFT_TO_UP", IBlockLeftToUpWallKickData));
	WallKickDataMap.insert(std::make_pair("IBLOCK_UP_TO_LEFT", IBlockUpToLeftWallKickData));

}

std::pair<std::string, GLuint> AssetLoader::LoadTexture(std::string _TextureName, std::string _AssetFilePath) {
	GLuint Tex;
	
	glGenTextures(1, &Tex);
	glBindTexture(GL_TEXTURE_2D, Tex);

	//getting the image data from filepath
	int Width, Height;
	unsigned char* ImageData = SOIL_load_image(
		_AssetFilePath.c_str(),
		&Width, &Height,
		0,
		SOIL_LOAD_RGBA
	);

	//Generating the texture from image data
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		Width, Height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		ImageData
	);

	//Generating mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Setting texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Freeing up data
	SOIL_free_image_data(ImageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	return std::make_pair(_TextureName, Tex);
}

std::pair<std::string, class Shader*> AssetLoader::LoadShader(std::string _ShaderName, const char* _VertData, const char* _FragData) {
	Shader* s = new Shader();
	s->SetShaderName(_ShaderName);
	s->SetVertexShaderData(_VertData);
	s->SetFragmentShaderData(_FragData);
	s->InitShader();
	return std::make_pair(_ShaderName, s);
}
