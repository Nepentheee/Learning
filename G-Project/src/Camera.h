#pragma once

#include "glm/glm.hpp"

class Camera
{
private:
	glm::vec3 m_CameraPos;
public:
	Camera(glm::vec3 cameraPos);
	~Camera();
};