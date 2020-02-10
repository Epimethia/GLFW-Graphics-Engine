#include "AssetLoader.h"

#include "Dependencies/SOIL/include/SOIL.h"
#include "Dependencies/GLFW/include/glfw3.h"
#include "Shader.h"
#include "DefaultShader.h"
#include <iostream>

std::map<std::string, GLuint> AssetLoader::TextureMap;
std::map<std::string, Shader*> AssetLoader::ShaderMap;

void AssetLoader::LoadAssets() {
	//std::string DefaultPath = "";
	//Load brick texture
	TextureMap.insert(LoadAsset("TEX_BRICK_BLUE","Assets/Textures/Brick Textures/blue.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_GREEN","Assets/Textures/Brick Textures/green.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_YELLOW","Assets/Textures/Brick Textures/yellow.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_PURPLE","Assets/Textures/Brick Textures/purple.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_ORANGE","Assets/Textures/Brick Textures/orange.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_RED","Assets/Textures/Brick Textures/red.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_CYAN","Assets/Textures/Brick Textures/cyan.png"));
	TextureMap.insert(LoadAsset("TEX_BRICK_GRAY","Assets/Textures/Brick Textures/gray.png"));
	TextureMap.insert(LoadAsset("UI_BG_MAIN","Assets/Textures/UI/background.png"));

	ShaderMap.insert(LoadShader("DEFAULT_SHADER", DefaultShaderData::VertexData, DefaultShaderData::FragmentData));
}

std::pair<std::string, GLuint> AssetLoader::LoadAsset(std::string _TextureName, std::string _AssetFilePath) {
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
