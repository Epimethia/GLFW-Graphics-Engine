#pragma once
#include <vector>
#include "Shader.h"

#include "Dependencies/GLEW/include/glew.h"
#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"

class Sprite {
private:
	std::vector<float> m_VertexData;

	GLuint m_VertexBufferObject = 0;
	GLuint m_VertexArrayObject = 0;
	GLuint m_Tex = 0;
	//GLuint m_ShaderProgram = 0;
	Shader* m_ShaderProgram = nullptr;

	glm::mat4 m_VPMatrix;
	glm::mat4 m_MVPMatrix;

	glm::vec2 m_ObjectPosition = { 30.0f, 30.0f };
	float m_ObjectRotation = 0.0f;
	glm::vec2 m_LocalOffset = { 0.0f, 0.0f };
	glm::vec2 m_ObjectScale = { 1.0f, 1.0f };

public:
	
	Sprite();
	~Sprite();

	void Init();
	void Render();

	//void SetProgram(GLuint _Program) { m_ShaderProgram = _Program; };
	void SetShader(Shader* _Shader) { m_ShaderProgram = _Shader; };
	void SetVPMatrix(glm::mat4 _Matrix) { m_VPMatrix = _Matrix; };
	void SetTexture(GLuint _Tex) { m_Tex = _Tex; };
	void SetObjectPosition(glm::vec2 _Position) { m_ObjectPosition = _Position; };
	glm::vec2 GetObjectPosition() { return m_ObjectPosition; };
	void SetLocalOffset(glm::vec2 _LocalOffset) { m_LocalOffset = _LocalOffset; };
	void SetObjectScale(glm::vec2 _ObjectScale) { m_ObjectScale = _ObjectScale; };
};

