#include "Model.h"

Model::Model(float vertices[], unsigned int vertexLength, unsigned int indices[], unsigned int indexLength, string shaderPath, string texturePath) 
{
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, vertexLength);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	VAO = std::make_unique<VertexArray>();
	VAO->AddBuffer(*m_VertexBuffer, layout);

	IBO = std::make_unique<IndexBuffer>(indices, indexLength / sizeof(unsigned int));
	ModelShader = std::make_unique<Shader>(shaderPath);

	if (texturePath != "")
	{
		m_Texture = std::make_unique<Texture>(texturePath);
	}
}

Model::~Model()
{
}

