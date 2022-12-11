#pragma once
#include "Renderer.h"

class FrameBuffer
{
private:
	unsigned int m_RenderID;
	unsigned int m_ColorTextureID;
	unsigned int m_RenderBufferObjID;

public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	bool IsComplete();
	unsigned int GetColorTextureID();
	unsigned int GetRenderBufferObjID();
};
