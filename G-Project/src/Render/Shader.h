#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <glad/glad.h>
#include "glm/glm.hpp"

using namespace std;

class Shader
{
public:
	Shader(const string& filePath);
	Shader(const string& vertFilePath, const string& fragFilePath);
	~Shader();

	void Bind() const;
	void BindTexture(unsigned int slotID, unsigned int textureID) const;
	void BindCubeMapTexture(unsigned int textureID) const;
	void SetBool(const string& name, bool value);
	void SetUnitform1i(const string& name, int value);
	void SetUniform3f(const string& name, glm::uvec3 value);
	void SetUniform3f(const string& name, float v1, float v2, float v3);
	void SetUniform3f(const string& name, float floatArray[]);
	void SetUniform4f(const string& name, glm::uvec4 value);
	void SetUniform4f(const string& name, float v1, float v2, float v3, float v4);
	void SetUniform1f(const string& name, float v1);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1iv(const std::string& name, int count, int* value);
private:
	unsigned int m_RenderID;
	map<string, int> m_UniformMap;
	inline int GetUniformLocaton(unsigned int renderID, const std::string& name);
	inline void GetShaderCodeFromFile(const char* path, string& vectexCode, string& fragmentCode);
	inline void GetShaderCodeFromFile(const char* path, string& code);
	inline unsigned int CreateShader(int type, const char* code);
};

