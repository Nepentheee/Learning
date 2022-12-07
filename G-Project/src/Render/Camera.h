#pragma once

#include "glm/glm.hpp"
#include "Renderer.h"

class Camera
{
private:
	float m_Fov;
	float m_Yaw;
	float m_Pitch;
	float m_MoveSpeed;
	
	float m_LastOffsetX;
	float m_LastOffsetY;

	bool m_FirstMove;
	bool m_Orthographic;

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
public:
	Camera(bool orthographic = false);
	~Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectMatrix();

	void SetFov(float fov);
	float GetFov();
	void SetOrthographic(bool orthographic);
	bool IsOrthographic();
	void ProcessKeyboard(int direction, float deltaTime);
	void ProcessMouseMove(float xpos, float ypos);
	void ProcessScrollMove(float xpos, float ypos);
};