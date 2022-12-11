#pragma once

#include <VertexBufferLayout.h>
#include "Texture.h"

class RenderObj
{
private:
	Texture* m_Textures[16];

public:
	std::unique_ptr<VertexArray> VAO;
	std::unique_ptr<IndexBuffer> IBO;
	std::unique_ptr<Shader> ModelShader;

	RenderObj(string shaderPath, VertexBufferLayout layout, const float vertices[], unsigned int vertexLength, const unsigned int indices[], unsigned int indexLength, string texturePath[], unsigned int textureLength);
	RenderObj(string vertexPath, string fragPath, VertexBufferLayout layout, const float vertices[], unsigned int vertexLength, const unsigned int indices[], unsigned int indexLength, string texturePath[], unsigned int textureLength);
	~RenderObj();
	void BindTextures();
};

