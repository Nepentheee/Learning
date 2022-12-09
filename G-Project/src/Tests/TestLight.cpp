#include "TestLight.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace test
{
	TestLight::TestLight() : m_RotateAngle(0), m_LightOffset{ 1,0 }, m_GLLineMode(false), 
		m_Color{ 0.2f, 0.3f, 0.8f, 1.0f },
		m_DirectionLight { 0.2f, 1.0f, 0.3f }
	{
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_LightModel = std::make_unique<RenderObj>(
			LightCasterShaderPath, 
			layout,
			vertices, sizeof(vertices), 
			indices, sizeof(indices), 
			nullptr, 0);

		m_CubeModel = std::make_unique<RenderObj>(
			LightingVertexShaderPath, LightingFragShaderPath,
			layout,
			vertices, sizeof(vertices), 
			indices, sizeof(indices), 
			new string[] { Testure1Path, DiffuseMapPath, SpecularMap }, 3);
		
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

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();

		// Draw Light
		{
			glm::mat4 lightModel = glm::translate(glm::mat4(1), glm::vec3(m_DirectionLight[0], m_DirectionLight[1], m_DirectionLight[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
			glm::mat4 mvp = proj * view * lightModel;

			m_LightModel->ModelShader->Bind();
			m_LightModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
			m_LightModel->ModelShader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

			m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
		
			/*for (int i = 0; i < 4; ++i)
			{
				glm::mat4 lightModel = glm::translate(glm::mat4(1), pointLightPositions[i]) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
				glm::mat4 mvp = proj * view * lightModel;

				m_LightModel->ModelShader->Bind();
				m_LightModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
				m_LightModel->ModelShader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

				m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
			}*/
		}

		// Draw Cube
		{
			//glm::mat4 cubeModel = glm::rotate(glm::mat4(1), glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 cubeModel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
			cubeModel = glm::scale(cubeModel, glm::vec3(0.2f));
			cubeModel = glm::rotate(glm::mat4(1), glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));;
			glm::mat4 mvp = proj * view * cubeModel;

			m_CubeModel->ModelShader->Bind();
			m_CubeModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
			m_CubeModel->ModelShader->SetUniformMat4f("u_Model", cubeModel);
			m_CubeModel->ModelShader->SetUnitform1i("u_Texture", 0);
			m_CubeModel->ModelShader->SetUniform3f("u_viewPos", m_Camera->GetCameraPos());

			// Material
			m_CubeModel->ModelShader->SetUnitform1i("u_material.shininess", 32);
			m_CubeModel->ModelShader->SetUnitform1i("u_material.diffuse", 1);
			m_CubeModel->ModelShader->SetUnitform1i("u_material.specular", 2);

			// Direction Light
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.direction", -m_DirectionLight[0], -m_DirectionLight[1], -m_DirectionLight[2]);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.ambient", 0.05f, 0.05f, 0.05f);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.diffuse", 1.4f, 1.4f, 1.4f);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.specular", 1.5f, 1.5f, 1.5f);

			// Spot Light
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.position", m_Camera->GetCameraPos());
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.direction", m_Camera->GetCameraFront());
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.ambient", 0.0f, 0.0f, 0.0f);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.specular", 1.0f, 1.0f, 1.0f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.constant", 1.0f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.linear", 0.09f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		
			// PointLight
			{
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].position", pointLightPositions[0]);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].specular", 1.0f, 1.0f, 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);

				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].position", pointLightPositions[1]);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].specular", 1.0f, 1.0f, 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);

				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].position", pointLightPositions[2]);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].specular", 1.0f, 1.0f, 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);

				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].position", pointLightPositions[3]);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
				m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].specular", 1.0f, 1.0f, 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
				m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);
			}

			m_Renderer->Draw(*m_CubeModel->VAO, *m_CubeModel->IBO, *m_CubeModel->ModelShader);
		}
		
	}

	void TestLight::OnImGuiRender()
	{
		ImGui::Text("Fov %f", m_Camera->GetFov());
		ImGui::ColorEdit4("ClearColor", m_Color);
		ImGui::SliderFloat("m_RotateAngle", &m_RotateAngle, -360, 360);
		ImGui::SliderFloat2("m_LightOffset", m_LightOffset, -2, 2);
		ImGui::SliderFloat3("m_DirectionLight", m_DirectionLight, -3, 3);

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
