#pragma once

#include <iostream>
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak()

/* ��б�ܺ��治���пո� */
#define GLCall(x) do { \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));\
 } while (0)

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    const string ShaderPath = "Resources/Shaders/Basic.shader";

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};