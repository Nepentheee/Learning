#pragma once

#include <VertexBufferLayout.h>
#include "Texture.h"

class RenderObj
{
private:

public:
	std::unique_ptr<VertexArray> VAO;
	std::unique_ptr<IndexBuffer> IBO;
	std::unique_ptr<Shader> ModelShader;

	RenderObj(string shaderPath, VertexBufferLayout layout, float vertices[], unsigned int vertexLength, unsigned int indices[], unsigned int indexLength, string texturePath[], unsigned int textureLength);
	RenderObj(string vertexShader, string fragPath, VertexBufferLayout layout, float vertices[], unsigned int vertexLength, unsigned int indices[], unsigned int indexLength, string texturePath[], unsigned int textureLength);
	~RenderObj();
};

