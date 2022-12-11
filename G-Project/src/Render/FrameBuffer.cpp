#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_RenderID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);

	glGenTextures(1, &m_ColorTextureID);
	glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ScreenWidth, ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);

	glGenRenderbuffers(1, &m_RenderBufferObjID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObjID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ScreenWidth, ScreenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferObjID);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
}

bool FrameBuffer::IsComplete()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		return false;
	}
	return true;
}

unsigned int FrameBuffer::GetColorTextureID()
{
	return m_ColorTextureID;
}

unsigned int FrameBuffer::GetRenderBufferObjID()
{
	return m_RenderBufferObjID;
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}