#include "TestCubeMap.h"

namespace test
{
	TestCubeMap::TestCubeMap()
	{
		m_Camera = std::make_unique<Camera>();
		m_Renderer = std::make_unique<Renderer>();
		m_CubeMap = new CubeMap();

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_CubeObj = new RenderObj(
			BasicShaderPath,
			layout,
			CubeVertices, CubeVertexSize,
			CubeIndices, CubeIndexSize,
			new string[]{ Testure1Path }, 1);

		//float skyboxVertices[] = {
		//	// positions          
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,

		//	-1.0f, -1.0f,  1.0f,
		//	-1.0f, -1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	-1.0f, -1.0f,  1.0f,

		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,

		//	-1.0f, -1.0f,  1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f, -1.0f,  1.0f,
		//	-1.0f, -1.0f,  1.0f,

		//	-1.0f,  1.0f, -1.0f,
		//	 1.0f,  1.0f, -1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	 1.0f,  1.0f,  1.0f,
		//	-1.0f,  1.0f,  1.0f,
		//	-1.0f,  1.0f, -1.0f,

		//	-1.0f, -1.0f, -1.0f,
		//	-1.0f, -1.0f,  1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f,
		//	-1.0f, -1.0f,  1.0f,
		//	 1.0f, -1.0f,  1.0f
		//};

		float skyboxVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		VertexBufferLayout skyBoxLayout;
		skyBoxLayout.Push<float>(3);
		skyBoxLayout.Push<float>(3);

		m_MapObj = new RenderObj(
			CubeMapShaderPath,
			skyBoxLayout,
			skyboxVertices, sizeof(skyboxVertices),
			CubeIndices, CubeIndexSize,
			nullptr, 0);
	}

	TestCubeMap::~TestCubeMap()
	{
	}

	void TestCubeMap::OnRender()
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();
		glm::mat4 mvp = proj * view * model;

		m_Renderer->Clear();

		// Draw NormalCube
		m_CubeObj->ModelShader->Bind();
		m_CubeObj->BindTextures();
		m_CubeObj->ModelShader->SetUniformMat4f("u_MVP", mvp);
		m_CubeObj->ModelShader->SetUniform4f("u_Color", 1, 1, 1, 1);

		m_Renderer->Draw(*m_CubeObj->VAO, *m_CubeObj->IBO, *m_CubeObj->ModelShader);

		// Draw CubeMap
		glDepthFunc(GL_LEQUAL);

		// 消除Camera移动的影响
		//view = glm::mat4(glm::mat3(m_Camera->GetViewMatrix()));
		m_MapObj->ModelShader->Bind();
		m_MapObj->ModelShader->BindCubeMapTexture(m_CubeMap->GetCubeMapRenderID());
		m_MapObj->ModelShader->SetUniformMat4f("u_View", view);
		m_MapObj->ModelShader->SetUniformMat4f("u_Proj", proj);

		m_Renderer->Draw(*m_MapObj->VAO, *m_MapObj->IBO, *m_MapObj->ModelShader);

		m_MapObj->VAO->Unbind();

		//m_CubeMap->UnBind();

		glDepthFunc(GL_LESS);
	}

	void TestCubeMap::OnProcessInput(int keyCode, float deltaTime)
	{
		m_Camera->ProcessKeyboard(keyCode, deltaTime);
	}

	void TestCubeMap::OnScrollMove(float xOffset, float yOffset)
	{
		m_Camera->ProcessScrollMove(xOffset, yOffset);
	}

	void TestCubeMap::OnCameraOrthographicChange(bool isOrthographic)
	{
		m_Camera->SetOrthographic(isOrthographic);
	}
}
