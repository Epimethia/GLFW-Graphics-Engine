#include "Camera.h"

#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLM/gtc/matrix_transform.hpp"
#include "Dependencies/GLM/gtc/type_ptr.hpp"
#include "Window.h"
glm::mat4 Camera::m_VPMatrix;

Camera::Camera() {


}

Camera::~Camera() {}

void Camera::InitCamera() {
	glm::mat4 Projection = glm::ortho(0.0f, static_cast<float>(Window::GetWindowWidth()), 0.0f, static_cast<float>(Window::GetWindowHeight()), -1.0f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m_VPMatrix = Projection * View;
}
