#include "TestLight.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace test
{
	TestLight::TestLight() : m_RotateAngle(0), m_LightOffset{ 1,0 }, m_GLLineMode(false), m_Color{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
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

		m_CubeModel = std::make_unique<Model>(vertices, sizeof(vertices), indices, sizeof(indices), BasicShaderPath, Testure1Path);
		m_LightModel = std::make_unique<Model>(vertices, sizeof(vertices), indices, sizeof(indices), LightShaderPath, "");
		
		m_Camera = std::make_unique<Camera>();
		m_Renderer = std::make_unique<Renderer>();
	}

	TestLight::~TestLight()
	{
	}

	void TestLight::OnUpdate(float deltaTime)
	{
	}

	void TestLight::OnRender()
	{
		m_Renderer->Clear();

		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();

		// Draw Cube
		{
			glm::mat4 cubeModel = glm::rotate(glm::mat4(1), glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 mvp = proj * view * cubeModel;

			m_CubeModel->ModelShader->Bind();
			m_CubeModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
			m_CubeModel->ModelShader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

			m_Renderer->Draw(*m_CubeModel->VAO, *m_CubeModel->IBO, *m_CubeModel->ModelShader);
		}
		
		// Draw Light
		{
			glm::mat4 lightModel = glm::translate(glm::mat4(1), glm::vec3(m_LightOffset[0], m_LightOffset[1], 0)) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
			glm::mat4 mvp = proj * view * lightModel;

			m_LightModel->ModelShader->Bind();
			m_LightModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
			m_LightModel->ModelShader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

			m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
		}
	}

	void TestLight::OnImGuiRender()
	{
		ImGui::Text("Fov %f", m_Camera->GetFov());
		ImGui::ColorEdit4("ClearColor", m_Color);
		ImGui::SliderFloat("m_RotateAngle", &m_RotateAngle, -360, 360);
		ImGui::SliderFloat2("m_LightOffset", m_LightOffset, -2, 2);

		if (ImGui::RadioButton("Orthographic", m_Camera->IsOrthographic()))
		{
			m_Camera->SetOrthographic(true);
		}

		if (ImGui::RadioButton("Perspective", !m_Camera->IsOrthographic()))
		{
			m_Camera->SetOrthographic(false);
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
	}

	void TestLight::OnProcessInput(int keyCode, float deltaTime)
	{
		m_Camera->ProcessKeyboard(keyCode, deltaTime);
	}

	void TestLight::OnMouseMove(float xPos, float yPos)
	{
		m_Camera->ProcessMouseMove(xPos, yPos);
	}

	void TestLight::OnScrollMove(float xOffset, float yOffset)
	{
		m_Camera->ProcessScrollMove(xOffset, yOffset);
	}
}
