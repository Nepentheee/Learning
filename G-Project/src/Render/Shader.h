#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "glm/glm.hpp"

using namespace std;

class Shader
{
public:
	Shader(const char* filePath);
	~Shader();

	void Bind() const;
	void SetBool(const string& name, bool value);
	void SetInt(const string& name, int value);
	void SetFloat4(const string& name, float v1, float v2, float v3, float v4);
	void SetFloat1(const string& name, float v1);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1iv(const std::string& name, int count, int* value);
private:
	unsigned int m_RenderID;
	inline void GetShaderCodeFromFile(const char* path, string& vectexCode, string& fragmentCode);
	inline unsigned int CreateShader(int type, const char* code);
};
