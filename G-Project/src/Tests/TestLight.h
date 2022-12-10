#pragma once

#include "Test.h"
#include "RenderObj.h"

namespace test
{
	class TestLight : public Test
	{
	private:
		float m_DirLightColor[3];
		float m_PointLightColor[3];
		float m_SpotLightColor[3];
		int m_SpecularShininess;
		float m_RotateAngle;
		float m_LightRatio[4];
		float m_DirLightPos[3];
		float m_PointLightPos[3];
		float m_SpotLightPos[3];

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
		void OnCameraOrthographicChange(bool isOrthographic) override;
	};
}
