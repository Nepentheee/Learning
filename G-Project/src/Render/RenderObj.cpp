#include "RenderObj.h"

RenderObj::RenderObj(
	string shaderPath, VertexBufferLayout layout,
	float vertices[], unsigned int vertexLength, 
	unsigned int indices[], unsigned int indexLength, 
	string texturePaths[], unsigned int textureLength)
{
	VertexBuffer* vertexBuffer = new VertexBuffer(vertices, vertexLength);

	VAO = std::make_unique<VertexArray>();
	VAO->AddBuffer(*vertexBuffer, layout);

	IBO = std::make_unique<IndexBuffer>(indices, indexLength / sizeof(unsigned int));
	ModelShader = std::make_unique<Shader>(shaderPath);

	if (textureLength > 0)
	{
		for (int i = 0; i < textureLength; ++i)
		{
			Texture* texture = new Texture(texturePaths[i]);
			texture->Bind(i);
		}
	}
}

RenderObj::RenderObj(
	string vertexPath, string fragPath,
	VertexBufferLayout layout,
	float vertices[], unsigned int vertexLength,
	unsigned int indices[], unsigned int indexLength,
	string texturePaths[], unsigned int textureLength)
{
	VertexBuffer* vertexBuffer = new VertexBuffer(vertices, vertexLength);

	VAO = std::make_unique<VertexArray>();
	VAO->AddBuffer(*vertexBuffer, layout);

	IBO = std::make_unique<IndexBuffer>(indices, indexLength / sizeof(unsigned int));
	ModelShader = std::make_unique<Shader>(vertexPath, fragPath);

	if (textureLength > 0)
	{
		Texture* textures[10];

		for (int i = 0; i < textureLength; ++i)
		{
			textures[i] = new Texture(texturePaths[i]);
		}

		for (int i = 0; i < textureLength; ++i)
		{
			textures[i]->Bind(i);
		}
	}
}

RenderObj::~RenderObj()
{
}

