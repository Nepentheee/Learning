#pragma once

#include <VertexBufferLayout.h>
#include "Texture.h"

class Model
{
private:
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<Texture> m_Texture;

public:
	std::unique_ptr<VertexArray> VAO;
	std::unique_ptr<IndexBuffer> IBO;
	std::unique_ptr<Shader> ModelShader;

	Model(float vertices[], unsigned int vertexLength, unsigned int indices[], unsigned int indexLength, string shaderPath, string texturePath);
	~Model();
};

