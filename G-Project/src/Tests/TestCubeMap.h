#pragma once

#include "Test.h"
#include "CubeMap.h"
#include "RenderObj.h"

namespace test
{
	class TestCubeMap : public Test
	{
	private:
		CubeMap* m_CubeMap;

		RenderObj* m_CubeObj;
		RenderObj* m_MapObj;

	public:
		TestCubeMap();
		~TestCubeMap();

		void OnRender() override;
		void OnProcessInput(int keyCode, float deltaTime) override;
		void OnScrollMove(float xOffset, float yOffset) override;
		void OnCameraOrthographicChange(bool isOrthographic) override;
	};
}
