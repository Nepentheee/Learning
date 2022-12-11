#pragma once
#include "Renderer.h"

class CubeMap
{
private:
	unsigned int m_RenderID;

public:
	CubeMap();
	~CubeMap();

	void Bind() const;
	void UnBind() const;

	unsigned int GetCubeMapRenderID();
};

