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
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0f, 1.0f);\n"
"    color = vCol;\n"
"}\n";

//Fragment Shader
const char* DefaultShaderData::FragmentData =
"#version 430\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0f);\n"
"}\n";



