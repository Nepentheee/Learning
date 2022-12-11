#include "TestFrameBuffer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	TestFrameBuffer::TestFrameBuffer()
	{
		m_FrameBufferObj = new FrameBuffer();

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = {
			 0,  1,  2,  3,  4,  5,
			 6,  7,  8,  9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35,
		};

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_CubeObj = new RenderObj(
			BasicShaderPath,
			layout,
			vertices, sizeof(vertices),
			indices, sizeof(indices),
			new string[] { Testure1Path }, 1);

		float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 0
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 1
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // 2
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // 3
		};
		
		unsigned int quadIndices[] = {
			0, 1, 2,
			2, 3, 0,
		};
		
		m_QuadObj = new RenderObj(
			FrameBufferShaderPath,
			layout,
			quadVertices, sizeof(quadVertices),
			quadIndices, sizeof(quadIndices),
			nullptr, 0);

		m_Camera = std::make_unique<Camera>();
		m_Renderer = std::make_unique<Renderer>();
	}

	TestFrameBuffer::~TestFrameBuffer()
	{
	}

	void TestFrameBuffer::OnUpdate(float deltaTime)
	{
	}

	void TestFrameBuffer::OnRender()
	{
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();

		// Use FrameBuffer Draw Cube
		m_FrameBufferObj->Bind();

		m_Renderer->Clear();

		glEnable(GL_DEPTH_TEST);

		for (size_t i = 0; i < 2; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i == 0 ? -0.5f : 0.5f, 0.0f, 0.0f));
			m_CubeObj->BindTextures();
			m_CubeObj->ModelShader->Bind();
			m_CubeObj->ModelShader->SetUniformMat4f("u_MVP", proj * view * model);
			m_CubeObj->ModelShader->SetUniform4f("u_Color", i == 0 ? 1 : 0, i == 1 ? 1 : 0, 0, 1);

			m_Renderer->Draw(*m_CubeObj->VAO, *m_CubeObj->IBO, *m_CubeObj->ModelShader);
		}
		
		m_FrameBufferObj->UnBind();

		// Draw Quad
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_QuadObj->ModelShader->Bind();
		m_QuadObj->ModelShader->BindTexture(0, m_FrameBufferObj->GetColorTextureID());

		m_Renderer->Draw(*m_QuadObj->VAO, *m_QuadObj->IBO, *m_QuadObj->ModelShader);

		glEnable(GL_DEPTH_TEST);
	}

	void TestFrameBuffer::OnImGuiRender()
	{
	}

	void TestFrameBuffer::OnProcessInput(int keyCode, float deltaTime)
	{
		m_Camera->ProcessKeyboard(keyCode, deltaTime);
	}

	void TestFrameBuffer::OnMouseMove(float xPos, float yPos)
	{
		m_Camera->ProcessMouseMove(xPos, yPos);
	}

	void TestFrameBuffer::OnScrollMove(float xOffset, float yOffset)
	{
		m_Camera->ProcessScrollMove(xOffset, yOffset);
	}

	void TestFrameBuffer::OnCameraOrthographicChange(bool isOrthographic)
	{
		m_Camera->SetOrthographic(isOrthographic);
	}
}
