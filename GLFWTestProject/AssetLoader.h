#pragma once
#include <map>
#include <string>
#include "Dependencies/GLEW/include/glew.h"

class AssetLoader {
public:

	static std::map<std::string, GLuint> TextureMap;
	static void LoadTextures();

private:
	static GLuint LoadAsset(std::string _AssetFilePath);

};

