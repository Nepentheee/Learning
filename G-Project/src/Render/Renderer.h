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
const string LightCasterShaderPath = "Resources/Shaders/LightCaster.shader";
const string BatchRenderShaderPath = "Resources/Shaders/BatchRender.shader";
const string LightingVertexShaderPath = "Resources/Shaders/Lighting.vert";
const string LightingFragShaderPath = "Resources/Shaders/Lighting.frag";
const string Testure1Path = "Resources/textures/IMG_1223.JPG";
const string Testure2Path = "Resources/textures/IMG_1421.JPG";
const string DiffuseMapPath = "Resources/textures/diffuseMap.png";
const string SpecularMap = "Resources/textures/specularMap.png";

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};