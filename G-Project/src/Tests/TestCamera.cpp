#include "TestCameram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace test
{
	TestCamera::TestCamera() : m_RotateAngle(0), m_Color{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
		float value = 1.0f;
		//float vertices[] = {
		//	-0.5f * value, -0.5f * value, 0.0f, 0.0f, // 0 左下
		//	 0.5f * value, -0.5f * value, 1.0f, 0.0f, // 1 右下
		//	 0.5f * value,  0.5f * value, 1.0f, 1.0f, // 2 右上
		//	-0.5f * value,  0.5f * value, 0.0f, 1.0f  // 3 左上
		//};

		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};*/

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

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
		m_Shader = std::make_unique<Shader>(BasicShaderPath);
		m_Texture = std::make_unique<Texture>(Testure1Path);
		m_Renderer = std::make_unique<Renderer>();
		m_Camera = std::make_unique<Camera>();
	}

	TestCamera::~TestCamera()
	{
	}

	void test::TestCamera::OnUpdate(float deltaTime)
	{
	}

	void TestCamera::OnRender()
	{
		m_Renderer->Clear();

		glm::mat4 model = glm::rotate(glm::mat4(1), glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();
		glm::mat4 mvp = proj * view * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

		m_Renderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestCamera::OnImGuiRender()
	{
		ImGui::Text("Fov %f", m_Camera->GetFov());
		ImGui::ColorEdit4("ClearColor", m_Color);
		ImGui::SliderFloat("m_RotateAngle", &m_RotateAngle, -360, 360);

		// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void TestCamera::OnProcessInput(int keyCode, float deltaTime)
	{
		m_Camera->ProcessKeyboard(keyCode, deltaTime);
	}

	void TestCamera::OnMouseMove(float xPos, float yPos)
	{
		m_Camera->ProcessMouseMove(xPos, yPos);
	}

	void TestCamera::OnScrollMove(float xOffset, float yOffset)
	{
		m_Camera->ProcessScrollMove(xOffset, yOffset);
	}

	void TestCamera::OnCameraOrthographicChange(bool isOrthographic)
	{
		m_Camera->SetOrthographic(isOrthographic);
	}
}
