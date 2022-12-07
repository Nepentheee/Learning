#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"

namespace test
{
	class Test
	{
	protected:
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;

	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnProcessInput(int keyCode, float deltaTime) {}
		virtual void OnMouseMove(float xPos, float yPos) {}
		virtual void OnScrollMove(float xOffset, float yOffset) {}
	};

	class TestMenu: public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	public:
		TestMenu(Test*& currentTestPtr);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Register test: " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	};
}