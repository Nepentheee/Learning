#pragma once

#include "Test.h"
#include "RenderObj.h"

namespace test
{
	class TestLight : public Test
	{
	private:
		bool m_GLLineMode;
		float m_Color[4];
		float m_RotateAngle;
		float m_LightOffset[2];
		float m_DirectionLight[3];

		std::unique_ptr<RenderObj> m_CubeModel;
		std::unique_ptr<RenderObj> m_LightModel;

	public:
		TestLight();
		~TestLight();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnProcessInput(int keyCode, float deltaTime) override;
		void OnMouseMove(float xPos, float yPos) override;
		void OnScrollMove(float xOffset, float yOffset) override;
	};
}
