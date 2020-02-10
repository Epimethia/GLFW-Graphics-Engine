#pragma once
#include <map>
#include <string>
#include "Dependencies/GLEW/include/glew.h"

class AssetLoader {
public:

	static std::map<std::string, GLuint> TextureMap;
	static std::map<std::string, class Shader*> ShaderMap;
	static void LoadAssets();

private:
	static std::pair<std::string, GLuint> LoadAsset(std::string _TextureName, std::string _AssetFilePath);
	static std::pair<std::string, class Shader*> LoadShader(std::string _ShaderName, const char* _VertData, const char* _FragData);

};

