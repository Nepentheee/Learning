#include "Shader.h"

Shader::Shader(const string& filePath)
{
	string vertexCode;
	string fragmentCode;

	GetShaderCodeFromFile((char*) filePath.c_str(), vertexCode, fragmentCode);

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

Shader::Shader(const string& vertFilePath, const string& fragFilePath)
{
	string vertexCode;
	string fragmentCode;

	GetShaderCodeFromFile((char*)vertFilePath.c_str(), vertexCode);
	GetShaderCodeFromFile((char*)fragFilePath.c_str(), fragmentCode);

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

void Shader::Bind() const
{
	glUseProgram(m_RenderID);
}

void Shader::SetBool(const string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), (int)value);
}

void Shader::SetUnitform1i(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), value);
}

void Shader::SetUniform1f(const string& name, float v1)
{
	glUniform1f(glGetUniformLocation(m_RenderID, name.c_str()), v1);
}

void Shader::SetUniform3f(const string& name, glm::uvec3 value)
{
	glUniform3f(glGetUniformLocation(m_RenderID, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetUniform3f(const string& name, float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(m_RenderID, name.c_str()), v1, v2, v3);
}

void Shader::SetUniform4f(const string& name, glm::uvec4 value)
{
	glUniform4f(glGetUniformLocation(m_RenderID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform4f(const string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(m_RenderID, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_RenderID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1iv(const std::string& name, int count, int* value)
{
	glUniform1iv(glGetUniformLocation(m_RenderID, name.c_str()), count, value);
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

inline void Shader::GetShaderCodeFromFile(const char* path, string& code)
{
	string line;
	ifstream file(path);
	stringstream stream;
	while (getline(file, line))
	{
		stream << line << endl;
	}

	code = stream.str();
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
