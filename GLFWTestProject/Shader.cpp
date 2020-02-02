#include "Shader.h"
#include "Dependencies/glew/include/glew.h"
//#include "Dependencies/GLFW/include/glfw3.h"

#include <vector>
#include <iostream>

Shader::Shader() {}

Shader::~Shader() {}

bool Shader::InitShader() {
	//If either of the shader data is the default shader data, return, as they are
	//needed to create the shader.
	if (m_VertShaderData == "NONE" || m_FragShaderData == "NONE") {
		printf("ERROR::Shader Data Invalid \n");
		return false;
	}
	
	//Create shaders
	m_VertexShaderRef = CreateShader(GL_VERTEX_SHADER, m_VertShaderData);
	m_FragmentShaderRef = CreateShader(GL_FRAGMENT_SHADER, m_FragShaderData);

	//Create the shader program and link the shaders to it
	m_ShaderProgramRef = glCreateProgram();
	glAttachShader(m_ShaderProgramRef, m_VertexShaderRef);
	glAttachShader(m_ShaderProgramRef, m_FragmentShaderRef);
	glLinkProgram(m_ShaderProgramRef);

	int LinkResult = 0;
	glGetProgramiv(m_ShaderProgramRef, GL_LINK_STATUS, &LinkResult);
	if (LinkResult == GL_FALSE) {

		int InfoLogLength = 0;
		glGetProgramiv(m_ShaderProgramRef, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramLog(InfoLogLength);
		glGetProgramInfoLog(m_ShaderProgramRef, InfoLogLength, NULL, &ProgramLog[0]);

		std::string ErrorString = "Shader Loader : LINK ERROR\n";
		ErrorString += &ProgramLog[0];
		printf((ErrorString + "\n").c_str());
		return false;
	}

	return true;
}

unsigned int Shader::CreateShader(GLenum _ShaderType, std::string _SourceData) {

	const char* ShaderSourceData = _SourceData.c_str();
	const int ShaderSourceSize = static_cast<int>(_SourceData.size());

		//Create the shader
	unsigned int TempShader = glCreateShader(_ShaderType);
	glShaderSource(TempShader, 1, &ShaderSourceData, NULL);
	glCompileShader(TempShader);

	//Check for errors
	int CompileResult = 0;
	glGetShaderiv(TempShader, GL_COMPILE_STATUS, &CompileResult);
	if (CompileResult == GL_FALSE) {

		int info_log_length = 0;
		glGetShaderiv(TempShader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(TempShader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << m_ShaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return TempShader;
}
