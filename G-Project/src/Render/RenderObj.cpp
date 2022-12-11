#include "RenderObj.h"

RenderObj::RenderObj(
	string shaderPath, VertexBufferLayout layout,
	const float vertices[], unsigned int vertexLength, 
	const unsigned int indices[], unsigned int indexLength,
	string texturePaths[], unsigned int textureLength)
{
	Log("VertexLength " << vertexLength);
	Log("indexLength " << indexLength);
	VertexBuffer* vertexBuffer = new VertexBuffer(vertices, vertexLength);

	VAO = std::make_unique<VertexArray>();
	VAO->AddBuffer(*vertexBuffer, layout);

	IBO = std::make_unique<IndexBuffer>(indices, indexLength / sizeof(unsigned int));
	ModelShader = std::make_unique<Shader>(shaderPath);

	if (textureLength > 0)
	{
		for (int i = 0; i < textureLength; ++i)
		{
			m_Textures[i] = new Texture(texturePaths[i]);
		}

		for (int i = 0; i < textureLength; ++i)
		{
			m_Textures[i]->Bind(i);
		}
	}
}

RenderObj::RenderObj(
	string vertexPath, string fragPath,
	VertexBufferLayout layout,
	const float vertices[], unsigned int vertexLength,
	const unsigned int indices[], unsigned int indexLength,
	string texturePaths[], unsigned int textureLength)
{
	VertexBuffer* vertexBuffer = new VertexBuffer(vertices, vertexLength);

	VAO = std::make_unique<VertexArray>();
	VAO->AddBuffer(*vertexBuffer, layout);

	IBO = std::make_unique<IndexBuffer>(indices, indexLength / sizeof(unsigned int));
	ModelShader = std::make_unique<Shader>(vertexPath, fragPath);

	if (textureLength > 0)
	{
		for (int i = 0; i < textureLength; ++i)
		{
			m_Textures[i] = new Texture(texturePaths[i]);
		}

		for (int i = 0; i < textureLength; ++i)
		{
			m_Textures[i]->Bind(i);
		}
	}
}

RenderObj::~RenderObj()
{
}

void RenderObj::BindTextures()
{
	for (int i = 0; i < 16; ++i)
	{
		if (m_Textures[i] != nullptr)
		{
			m_Textures[i]->Bind(i);
		}
		else
		{
			break;
		}
	}
}