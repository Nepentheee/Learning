#include "TestLight.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

namespace test
{
	TestLight::TestLight() :
		m_RotateAngle(45), m_SpecularShininess(256),
		m_LightRatio{ 0.1f, 0.4f, 1.0f },
		m_DirLightColor{ 1.0f, 0.0f, 0.0f },
		m_PointLightColor{ 0.0f, 1.0f, 0.0f },
		m_SpotLightColor{ 0.0f, 0.0f, 1.0f },
		m_DirLightPos{ -2.0f, 1.5f, 1.0f },
		m_PointLightPos{ 0.0f, 0.0f, 4.0f },
		m_SpotLightPos { 2.0f, 1.0f, 1.0f },
		m_TestCubePos1{ 0.0f, 0.5f, 0.0f },
		m_TestCubePos2{ 0.0f, -0.5f, 0.0f }
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
			new string[]{ Testure1Path, DiffuseMapPath, SpecularMap }, 3);

		m_Renderer = std::make_unique<Renderer>();

		m_Camera = std::make_unique<Camera>();
		m_Camera->SetFov(80);
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

		glDisable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 proj = m_Camera->GetProjectMatrix();
		
		// Draw Light
		{
			// Direction Light
			{
				glm::mat4 dlModel = glm::translate(glm::mat4(1), glm::vec3(m_DirLightPos[0], m_DirLightPos[1], m_DirLightPos[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
				glm::mat4 dlMvp = proj * view * dlModel;

				m_LightModel->ModelShader->Bind();
				m_LightModel->ModelShader->SetUniformMat4f("u_MVP", dlMvp);
				m_LightModel->ModelShader->SetUniform3f("u_Color", m_DirLightColor);

				m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
			}

			// Point Light
			{
				glm::mat4 plModel = glm::translate(glm::mat4(1), glm::vec3(m_PointLightPos[0], m_PointLightPos[1], m_PointLightPos[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
				glm::mat4 plMvp = proj * view * plModel;

				m_LightModel->ModelShader->Bind();
				m_LightModel->ModelShader->SetUniformMat4f("u_MVP", plMvp);
				m_LightModel->ModelShader->SetUniform3f("u_Color", m_PointLightColor);

				m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
			}

			// Spot Light
			{
				glm::mat4 splModel = glm::translate(glm::mat4(1), glm::vec3(m_SpotLightPos[0], m_SpotLightPos[1], m_SpotLightPos[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
				glm::mat4 splMvp = proj * view * splModel;

				m_LightModel->ModelShader->Bind();
				m_LightModel->ModelShader->SetUniformMat4f("u_MVP", splMvp);
				m_LightModel->ModelShader->SetUniform3f("u_Color", m_SpotLightColor);

				m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
			}
		}

		// test Cube 1
		{
			glm::mat4 t1Model = glm::translate(glm::mat4(1), glm::vec3(m_TestCubePos1[0], m_TestCubePos1[1], m_TestCubePos1[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));

			m_LightModel->ModelShader->Bind();
			m_LightModel->ModelShader->SetUniformMat4f("u_MVP", proj * view * t1Model);
			m_LightModel->ModelShader->SetUniform3f("u_Color", glm::vec3(1, 0, 0));

			m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
		}

		// Draw Lighting Cube
		{
			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(0, 0, 0));
			model = glm::rotate(model, glm::radians(m_RotateAngle), glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			glm::mat4 mvp = proj * view * model;

			m_CubeModel->ModelShader->Bind();
			m_CubeModel->ModelShader->SetUniformMat4f("u_MVP", mvp);
			m_CubeModel->ModelShader->SetUniformMat4f("u_Model", model);
			m_CubeModel->ModelShader->SetUnitform1i("u_Texture", 0);
			m_CubeModel->ModelShader->SetUniform3f("u_viewPos", m_Camera->GetCameraPos());

			// Material
			m_CubeModel->ModelShader->SetUnitform1i("u_material.shininess", m_SpecularShininess);
			m_CubeModel->ModelShader->SetUnitform1i("u_material.diffuse", 1);
			m_CubeModel->ModelShader->SetUnitform1i("u_material.specular", 2);

			// Direction Light
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.direction", -m_DirLightPos[0], -m_DirLightPos[1], -m_DirLightPos[2]);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.color", m_DirLightColor);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.ambient", m_LightRatio[0], m_LightRatio[0], m_LightRatio[0]);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.diffuse", m_LightRatio[1], m_LightRatio[1], m_LightRatio[1]);
			m_CubeModel->ModelShader->SetUniform3f("u_dirLight.specular", m_LightRatio[2], m_LightRatio[2], m_LightRatio[2]);

			// PointLight
			m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].position", m_PointLightPos);
			m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].color", m_PointLightColor);
			m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].ambient", m_LightRatio[0], m_LightRatio[0], m_LightRatio[0]);
			m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].diffuse", m_LightRatio[1], m_LightRatio[1], m_LightRatio[1]);
			m_CubeModel->ModelShader->SetUniform3f("u_pointLights[0].specular", m_LightRatio[2], m_LightRatio[2], m_LightRatio[2]);
			m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
			m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
			m_CubeModel->ModelShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);

			// Spot Light
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.position", m_SpotLightPos);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.direction", -m_SpotLightPos[0], -m_SpotLightPos[1], -m_SpotLightPos[2]);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.color", m_SpotLightColor);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.ambient", 0.0f, 0.0f, 0.0f);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			m_CubeModel->ModelShader->SetUniform3f("u_spotLight.specular", 1.0f, 1.0f, 1.0f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.constant", 1.0f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.linear", 0.09f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			m_CubeModel->ModelShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

			m_Renderer->Draw(*m_CubeModel->VAO, *m_CubeModel->IBO, *m_CubeModel->ModelShader);
		}
		
		// 开启模版测试
		glEnable(GL_STENCIL_TEST);
		// 深度和模板都通过测试则替换
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		// 总是写入1
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xFF);
		
		// test Cube 2
		{
			glm::mat4 t2Model = glm::translate(glm::mat4(1), glm::vec3(m_TestCubePos2[0], m_TestCubePos2[1], m_TestCubePos2[2])) * glm::scale(glm::mat4(1), glm::vec3(0.3f));

			m_LightModel->ModelShader->Bind();
			m_LightModel->ModelShader->SetUniformMat4f("u_MVP", proj* view* t2Model);
			m_LightModel->ModelShader->SetUniform3f("u_Color", glm::vec3(0, 0, 1));

			m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
		}

		// 关闭深度测试、关闭写入，缓存buff≠1的才绘制
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		{
			glm::mat4 tScale2Model = glm::translate(glm::mat4(1), glm::vec3(m_TestCubePos2[0], m_TestCubePos2[1], m_TestCubePos2[2])) * glm::scale(glm::mat4(1), glm::vec3(0.36f));

			m_LightModel->ModelShader->Bind();
			m_LightModel->ModelShader->SetUniformMat4f("u_MVP", proj * view * tScale2Model);
			m_LightModel->ModelShader->SetUniform3f("u_Color", glm::vec3(1, 0, 0));

			m_Renderer->Draw(*m_LightModel->VAO, *m_LightModel->IBO, *m_LightModel->ModelShader);
		}

		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
	}

	void TestLight::OnImGuiRender()
	{
		// 光照参数
		/*{
			ImGui::ColorEdit3("DirLight Color", m_DirLightColor);
			ImGui::ColorEdit3("PointLight Color", m_PointLightColor);
			ImGui::ColorEdit3("SpotLight Color", m_SpotLightColor);
			ImGui::SliderFloat3("ambient/diffuse/specular", m_LightRatio, 0, 1);
			ImGui::SliderFloat3("DirLight Position", m_DirLightPos, -3, 4, "%.2f");
			ImGui::SliderFloat3("PointLight Position", m_PointLightPos, -3, 4, "%.2f");
			ImGui::SliderFloat3("SpotLight Position", m_SpotLightPos, -3, 4, "%.2f");
			ImGui::SliderInt("specular shininess", &m_SpecularShininess, 32, 256);
		}*/

		ImGui::Text("Fov %f", m_Camera->GetFov());
		ImGui::SliderFloat("Model RotateAngle", &m_RotateAngle, -180, 180);
		ImGui::SliderFloat3("1-TestCube Position", m_TestCubePos1, -3, 4, "%.2f");
		ImGui::SliderFloat3("2-TestCube Position", m_TestCubePos2, -3, 4, "%.2f");
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

	void TestLight::OnCameraOrthographicChange(bool isOrthographic)
	{
		m_Camera->SetOrthographic(isOrthographic);
	}
}
