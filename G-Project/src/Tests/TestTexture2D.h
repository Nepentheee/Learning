#pragma once

#include "Test.h"

#include <memory>
#include "glm/glm.hpp"

namespace test
{

	/* 清除颜色: 指的是用指定颜色填充背景色 刷屏 */
	class TestTexture2D : public Test
	{
	private:
		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}