#include "Shader.h"

Shader::Shader(const char* filePath)
{
	string vertexCode;
	string fragmentCode;

	GetShaderCodeFromFile(filePath, vertexCode, fragmentCode);

	/*cout << vertexCode << endl;
	cout << fragmentCode << endl;*/

	unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexCode.c_str());
	unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

	m_RenderID = glCreateProgram();
	glAttachShader(m_RenderID, vertexShader);
	glAttachShader(m_RenderID, fragmentShader);
	glLinkProgram(m_RenderID);

	// 打印连接错误（如果有的话）
	int success;
	glGetProgramiv(m_RenderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_RenderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(m_RenderID);
}

void Shader::SetBool(const string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), (int)value);
}

void Shader::SetInt(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), value);
}

void Shader::SetFloat4(const string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(m_RenderID, name.c_str()), v1, v2, v3, v4);
}

inline void Shader::GetShaderCodeFromFile(const char* path, string& vectexCode, string& fragmentCode)
{
	string line;
	ifstream file(path);
	stringstream stream[2];
	int index = 0;
	while (getline(file, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				index = 0;
			}
			else if (line.find("fragment") != string::npos)
			{
				index = 1;
			}
		}
		else
		{
			stream[index] << line << endl;
		}
	}

	vectexCode = stream[0].str();
	fragmentCode = stream[1].str();
}

inline unsigned int Shader::CreateShader(int type, const char* code)
{
	int id = glCreateShader(type);
	glShaderSource(id, 1, &code, 0);
	glCompileShader(id);

	// Compile Error
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		return 0;
	}

	return id;
}
