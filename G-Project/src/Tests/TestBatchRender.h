#pragma once

#include "Test.h"
#include "Texture.h"

#include <memory>
#include "glm/glm.hpp"

namespace test
{

	class TestBatchRender : public Test
	{
	private:
		std::unique_ptr<Texture> m_Textures[2];

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_Translation;

	public:
		TestBatchRender();
		~TestBatchRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}