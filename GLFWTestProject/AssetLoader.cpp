#include "AssetLoader.h"

#include "Dependencies/SOIL/include/SOIL.h"
#include "Dependencies/GLFW/include/glfw3.h"
#include <iostream>

std::map<std::string, GLuint> AssetLoader::TextureMap;

void AssetLoader::LoadTextures() {
	//std::string DefaultPath = "";
	//Load brick texture
	TextureMap.insert(std::make_pair(std::string("TEX_BRICK"), LoadAsset("Assets/Textures/brick.png")));
}

GLuint AssetLoader::LoadAsset(std::string _AssetFilePath) {
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Freeing up data
	SOIL_free_image_data(ImageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLboolean ispresent;
	bool failed = glAreTexturesResident(1, &Tex, &ispresent);

	return Tex;
}
