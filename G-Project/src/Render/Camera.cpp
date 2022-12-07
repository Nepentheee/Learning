#include "Camera.h"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(bool orthographic) : m_Orthographic(orthographic), m_Fov(45), m_MoveSpeed(1), m_FirstMove(true)
{
	m_CameraPos = glm::vec3(0, 0, 3.0f);
	m_CameraFront = glm::vec3(0, 0, -1.0f);
	m_CameraUp = glm::vec3(0, 1, 0);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(m_CameraUp, m_CameraFront));
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

glm::mat4 Camera::GetProjectMatrix()
{
	glm::mat4 proj = m_Orthographic
		? glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f)
		: glm::perspective(glm::radians(m_Fov), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);

	return proj;
}

void Camera::SetFov(float fov)
{
	m_Fov = fov;
}

float Camera::GetFov()
{
	return m_Fov;
}

void Camera::SetOrthographic(bool orthographic)
{
	m_Orthographic = orthographic;
}

bool Camera::IsOrthographic()
{
	return m_Orthographic;
}

void Camera::ProcessKeyboard(int direction, float deltaTime)
{
	float velocity = m_MoveSpeed * deltaTime;
	if (direction == 0) // up
		m_CameraPos += m_CameraFront * velocity;
	if (direction == 1) // down
		m_CameraPos -= m_CameraFront * velocity;
	if (direction == 2) // left
		m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
	if (direction == 3) // right
		m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
}

void Camera::ProcessMouseMove(float xpos, float ypos)
{
	if (m_FirstMove)
	{
		m_LastOffsetX = xpos;
		m_LastOffsetY = ypos;
		m_FirstMove = false;
	}

	float xoffset = xpos - m_LastOffsetX;
	float yoffset = m_LastOffsetY - ypos;
	m_LastOffsetX = xpos;
	m_LastOffsetY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	m_Pitch = glm::clamp(m_Pitch + yoffset, -89.0f, 89.0f);

	// dir.x = |ox| = |od| * cos(yaw) = cos(pitch) * cos(yaw)
	// dir.y = |oy| = sin(yaw)
	// dir.z = |oz| = |od| * sin(yaw) = cos(pitch) * sin(yaw)
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(front);
}

void Camera::ProcessScrollMove(float xOffset, float yOffset)
{
	m_Fov = glm::clamp(m_Fov - yOffset, 1.0f, 90.0f);
}

