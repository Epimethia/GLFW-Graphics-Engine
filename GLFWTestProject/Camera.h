#pragma once
#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"
class Camera {
public:

	Camera();
	~Camera();

	static void InitCamera();
	static glm::mat4 GetVPMatrix() { return m_VPMatrix; };


private:
	static glm::mat4 m_VPMatrix;
};

