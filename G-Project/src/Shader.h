#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

using namespace std;

class Shader
{
public:
	Shader(const char* filePath);
	~Shader();

	void Use();
	void SetBool(const string& name, bool value);
	void SetInt(const string& name, int value);
	void SetFloat4(const string& name, float v1, float v2, float v3, float v4);
private:
	unsigned int m_RenderID;
	inline void GetShaderCodeFromFile(const char* path, string& vectexCode, string& fragmentCode);
	inline unsigned int CreateShader(int type, const char* code);
};

