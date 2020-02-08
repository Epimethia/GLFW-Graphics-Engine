#include "Sprite.h"
#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"
#include <iostream>
Sprite::Sprite() {

	//Make the object simply a square for now
	m_VertexData.clear();

	m_VertexData = { 
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,		//Bottom Left
		0.0f, 32.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f,		//Top Left
		32.0f, 32.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,		//Top Right

		32.0f, 32.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,		//Top Right
		32.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f,			//Bottom Right
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f			//Bottom Left
	};

}

Sprite::~Sprite() {}

void Sprite::Init() {
	glGenVertexArrays(1, &m_VertexArrayObject);
	glGenBuffers(1, &m_VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, m_VertexData.size() * sizeof(float), m_VertexData.data(), GL_STATIC_DRAW);
	glBindVertexArray(m_VertexArrayObject);

	//size of the total data block
	unsigned int SizeOfDataBlock = sizeof(GLfloat) * 7;

	//Initializing attribute pointers
	//Positional
	glVertexAttribPointer(
		0, 2,						//Index and size
		GL_FLOAT,					//Type
		GL_FALSE,					//Is Normalized
		SizeOfDataBlock,			//Size of data block
		(GLvoid*)0					//Initial Offset (0 blocks)
	);
	glEnableVertexAttribArray(0);	//Binding to index 0

	//UV
	glVertexAttribPointer(
		1, 2,								//Index and size
		GL_FLOAT,							//Type
		GL_FALSE,							//Is Normalized
		SizeOfDataBlock,					//Size of data block
		(GLvoid*)(2 * sizeof(GLfloat))		//Initial offset (2 blocks)
	);
	glEnableVertexAttribArray(1);			//Binding attrib to index 2

	//Color
	glVertexAttribPointer(
		2, 3,								//Index and size
		GL_FLOAT,							//Type
		GL_FALSE,							//Is Normalized
		SizeOfDataBlock,					//Size of data block
		(GLvoid*)(4 * sizeof(GLfloat))		//Initial offset (4 blocks)
	);
	glEnableVertexAttribArray(2);			//Binding attrib to index 3

	//Clearing vertex references, to avoid data corruption when initializing other buffer/array objects.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::Render() {
	//init all the uniforms
	////Setting the MVP location in the shader program
	glUseProgram(m_ShaderProgram->GetShaderProgram());

	glm::mat4 Translation = glm::translate(glm::mat4(1.0f), glm::vec3((m_ObjectPosition + m_LocalOffset), 0.0f));
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_ObjectScale, 1.0f));
	glm::mat4 RotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_ObjectRotation), glm::vec3(0.0f, 0.0f, 1.0f));

	m_MVPMatrix = m_VPMatrix * (Translation * RotationZ * Scale);
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram->GetShaderProgram(), "InMVP"), 1, GL_FALSE, glm::value_ptr(m_MVPMatrix));

	//Setting and binding the correct texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex);

	//Sending the texture to the GPU via uniform
	glUniform1i(glGetUniformLocation(m_ShaderProgram->GetShaderProgram(), "InTex"), 0);

	glBindVertexArray(m_VertexArrayObject);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_VertexData.size()));
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);




}

void Sprite::RenderDebug() {


}
