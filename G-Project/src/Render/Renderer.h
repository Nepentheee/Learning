#pragma once

#include <iostream>
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak()

/* 反斜杠后面不能有空格 */
#define GLCall(x) do { \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));\
 } while (0)

#define Log(x) cout << x << endl;

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

const int ScreenWidth = 1290;
const int ScreenHeight = 960;
const string BasicShaderPath = "Resources/Shaders/Basic.shader";
const string FrameBufferShaderPath = "Resources/Shaders/FrameBuffer.shader";
const string LightCasterShaderPath = "Resources/Shaders/LightCaster.shader";
const string BatchRenderShaderPath = "Resources/Shaders/BatchRender.shader";
const string LightingVertexShaderPath = "Resources/Shaders/Lighting.vert";
const string LightingFragShaderPath = "Resources/Shaders/Lighting.frag";
const string CubeMapShaderPath = "Resources/Shaders/CubeMap.shader";

const string Testure1Path = "Resources/textures/IMG_1223.JPG";
const string Testure2Path = "Resources/textures/IMG_1421.JPG";
const string DiffuseMapPath = "Resources/textures/diffuseMap.png";
const string SpecularMap = "Resources/textures/specularMap.png";
const string GrassPath = "Resources/textures/grass.png";
const string BlendWindowPath = "Resources/textures/blendingWindow.png";

const string CubeMap0 = "Resources/textures/skybox/right.jpg";
const string CubeMap1 = "Resources/textures/skybox/left.jpg";
const string CubeMap2 = "Resources/textures/skybox/top.jpg";
const string CubeMap3 = "Resources/textures/skybox/bottom.jpg";
const string CubeMap4 = "Resources/textures/skybox/back.jpg";
const string CubeMap5 = "Resources/textures/skybox/front.jpg";

const float CubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
const unsigned int CubeVertexSize = sizeof(CubeVertices);

const unsigned int CubeIndices[] = {
	 0,  1,  2,  3,  4,  5,
	 6,  7,  8,  9, 10, 11,
	12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35,
};
const unsigned int CubeIndexSize = sizeof(CubeIndices);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};