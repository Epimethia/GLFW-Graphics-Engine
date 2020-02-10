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
"uniform mat4 InMVP;\n"
"layout (location = 0) in vec2 InPosition;\n"
"layout (location = 1) in vec2 InTexCoord;\n"
"layout (location = 2) in vec3 InColor;\n"
"out vec3 fragColor;\n"
"out vec2 fragTexCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = InMVP * vec4(InPosition, 0.0f, 1.0f);\n"
"    fragColor = InColor;\n"
"    fragTexCoord = InTexCoord;\n"
"}\n";

//Fragment Shader
const char* DefaultShaderData::FragmentData =
"#version 430\n"
"in vec3 fragColor;\n"
"in vec2 fragTexCoord;\n"
"uniform sampler2D InTex;\n"
"void main()\n"
"{\n"
"    gl_FragColor = texture(InTex, fragTexCoord);\n"

"}\n";

