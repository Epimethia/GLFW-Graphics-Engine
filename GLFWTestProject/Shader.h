#pragma once

#include <string>

class Shader {

private:
	unsigned int m_VertexShaderRef = 0;
	unsigned int m_FragmentShaderRef = 0;
	unsigned int m_ShaderProgramRef = 0;

	std::string m_VertShaderData = "NONE";
	std::string m_FragShaderData = "NONE";
	std::string m_ShaderName = "NONE";

public:

	Shader();
	~Shader();

	bool InitShader();
	unsigned int CreateShader(unsigned int _ShaderType, std::string _SourceData);

	//setters and getters
	void SetVertexShaderData(std::string _ShaderData) { m_VertShaderData = _ShaderData; };
	void SetFragmentShaderData(std::string _ShaderData) { m_FragShaderData = _ShaderData; };
	void SetShaderName(std::string _ShaderName) { m_ShaderName = _ShaderName; };
};

