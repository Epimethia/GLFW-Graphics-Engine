#pragma once

//------------------------------------------------------------------------------------------------
//Name:			Default Shader
//Description:	Takes the input positional values and multiplies it with the mvp
//				Color is determined by the passed in value. No textures.
//------------------------------------------------------------------------------------------------
class DefaultShaderData {
public:

	static const char* VertexData;
	static const char* FragmentData;
};

//Vertex Shader
const char* DefaultShaderData::VertexData =
"#version 430\n"
"uniform mat4 MVP;\n"
"layout (location = 0) in vec2 VPos;\n"
"layout (location = 2) in vec3 VCol;\n"
"out vec3 color;\n"
"out mat4 mvp;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(VPos, 0.0f, 1.0f);\n"
"    color = VCol;\n"
"    mvp = MVP;\n"
"}\n";

//Fragment Shader
const char* DefaultShaderData::FragmentData =
"#version 430\n"
"in vec3 color;\n"
"in mat4 mvp;\n"
"void main()\n"
"{\n"
//"    gl_FragColor = vec4(mvp[1][0], mvp[0][0], mvp[0][0], 1.0f);\n"
"    gl_FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n";


////Vertex Shader
//const char* DefaultShaderData::VertexData =
//"#version 430\n"
//"uniform mat4 MVP;\n"
//"attribute vec3 VCol;\n"
//"attribute vec2 VPos;\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = vec4(VPos, 0.0f, 1.0f);\n"
//"    color = VCol;\n"
//"}\n";
