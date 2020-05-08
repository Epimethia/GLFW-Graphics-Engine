#pragma once
#include <map>
#include <string>
#include <vector>
#include "Dependencies/GLEW/include/glew.h"

enum class EBlockTypes {
	O_BLOCK = 0,
	I_BLOCK,
	T_BLOCK,
	J_BLOCK,
	L_BLOCK,
	S_BLOCK,
	Z_BLOCK
};

class AssetLoader {
public:

	static std::map<std::string, GLuint> TextureMap;
	static std::map<std::string, class Shader*> ShaderMap;
	static void LoadAssets();
	static std::vector<EBlockTypes> GetRandomBagTemplate() { return RandomBagTemplateVect; };
	static std::map<std::string, std::vector<std::pair<int, int>>> WallKickDataMap;

private:
	static std::pair<std::string, GLuint> LoadTexture(std::string _TextureName, std::string _AssetFilePath);
	static std::pair<std::string, class Shader*> LoadShader(std::string _ShaderName, const char* _VertData, const char* _FragData);

	static std::vector<EBlockTypes> RandomBagTemplateVect;


};

