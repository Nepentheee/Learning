#include "TestCameram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "imgui.h"

namespace test
{
	TestCamera::TestCamera() : m_RotateAngle(0), m_Fov(30), m_Orthographic(false), m_GLLineMode(false)
	{
		glm::vec3 cameraPos = glm::vec3(0, 0, 3.0f);
		glm::vec3 cameraForward = glm::vec3(0, 0, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0, 1, 0);
		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraForward));
		Log("cameraForward " << glm::to_string(cameraForward));
		Log("cameraRight " << glm::to_string(cameraRight));
		Log("cameraUp " << glm::to_string(cameraUp));

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

		float halfWidth = ScreenWidth * 0.5f;
		float halfHeight = ScreenHeight * 0.5f;

		float value = 1.0f;
		float positions[] = {
			-0.5f * value, -0.5f * value, 0.0f, 0.0f, // 0 左下
			 0.5f * value, -0.5f * value, 1.0f, 0.0f, // 1 右下
			 0.5f * value,  0.5f * value, 1.0f, 1.0f, // 2 右上
			-0.5f * value,  0.5f * value, 0.0f, 1.0f  // 3 左上
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		m_Shader = std::make_unique<Shader>(BasicShaderPath);
		m_Texture = std::make_unique<Texture>(Testure1Path);
		m_Renderer = std::make_unique<Renderer>();
	}

	TestCamera::~TestCamera()
	{
	}

	void test::TestCamera::OnUpdate(float deltaTime)
	{
		TestTexture2D::OnUpdate(deltaTime);
	}

	void TestCamera::OnRender()
	{
		m_Renderer->Clear();

		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(ScreenWidth * 0.5f, ScreenHeight * 0.5f, 0));
		glm::mat4 model = glm::rotate(glm::mat4(1), glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		// 投影矩阵只能创建标准化的坐标
		glm::mat4 proj = m_Orthographic
			? glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f)
			: glm::perspective(glm::radians(m_Fov), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);

		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Renderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestCamera::OnImGuiRender()
	{
		ImGui::SliderFloat("m_Fov", &m_Fov, 0, 90);
		ImGui::SliderFloat("m_RotateAngle", &m_RotateAngle, -360, 360);

		if (ImGui::RadioButton("Orthographic", m_Orthographic))
		{
			m_Orthographic = true;
		}

		if (ImGui::RadioButton("Perspective", !m_Orthographic))
		{
			m_Orthographic = false;
		}

		if (ImGui::RadioButton("WareFrame: GL_LINE", m_GLLineMode))
		{
			m_GLLineMode = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (ImGui::RadioButton("WareFrame: GL_FIll", !m_GLLineMode))
		{
			m_GLLineMode = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
