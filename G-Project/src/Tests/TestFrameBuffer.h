#pragma once
#include "Test.h"
#include <RenderObj.h>
#include <FrameBuffer.h>

namespace test
{
	class TestFrameBuffer : public Test
	{
	private:
		FrameBuffer* m_FrameBufferObj;

		RenderObj* m_CubeObj;
		RenderObj* m_QuadObj;

	public:
		TestFrameBuffer();
		~TestFrameBuffer();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnProcessInput(int keyCode, float deltaTime) override;
		void OnMouseMove(float xPos, float yPos) override;
		void OnScrollMove(float xOffset, float yOffset) override;
		void OnCameraOrthographicChange(bool isOrthographic) override;
	};
}