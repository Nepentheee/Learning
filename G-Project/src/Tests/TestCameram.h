#pragma once

#include "Test.h"
#include "TestTexture2D.h"

namespace test
{
	class TestCamera : public TestTexture2D
	{
	private:
		float m_Fov;
		float m_RotateAngle;
		bool m_Orthographic;
		bool m_GLLineMode;
	public:
		TestCamera();
		~TestCamera();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}