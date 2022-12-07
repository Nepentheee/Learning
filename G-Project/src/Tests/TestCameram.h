#pragma once

#include "Test.h"
#include "TestTexture2D.h"

namespace test
{
	class TestCamera : public TestTexture2D
	{
	private:
		float m_Color[4];
		float m_RotateAngle;
		bool m_GLLineMode;
	public:
		TestCamera();
		~TestCamera();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnProcessInput(int keyCode, float deltaTime) override;
		void OnMouseMove(float xPos, float yPos) override;
		void OnScrollMove(float xOffset, float yOffset) override;
	};
}