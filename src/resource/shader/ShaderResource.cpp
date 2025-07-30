#include "resource/shader/ShaderResource.h"
#include "utility/FileData.h"

#include "glad/glad.h"
#include <iostream>

src::Shader::Shader(void)
	: m_shader(0), m_shaderType(EShaderType::INVALID_SHADER)
{
}

bool src::Shader::LoadResource(const char* fileName)
{
	// Check shader type (vert, frag, etc...)
	m_shaderType = ShaderType(fileName);

	if (m_shaderType == EShaderType::INVALID_SHADER)
		return false;

	// Load shader file to memory
	FileData fileData = fileData.ReadFile(fileName);

	if (!fileData.m_size)
	{
		std::printf("Failed to process shader '%s'. Shader file contains no content.\n", fileName);
		m_shaderType = EShaderType::INVALID_SHADER;
		return false;
	}

	// Create shader
	m_shader = glCreateShader(m_shaderType);
	// TODO: check if length (last param) needs to be nullptr
	glShaderSource(m_shader, 1, &fileData.m_fileContent, &fileData.m_size);
	glCompileShader(m_shader);

	int result;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		const int infoLogLength = 2500;
		char infoLog[infoLogLength];

		glGetShaderInfoLog(m_shader, infoLogLength, nullptr, infoLog);
		std::printf("Failed to compile shader. Error: %s", infoLog);
		m_shaderType = EShaderType::INVALID_SHADER;

		return false;
	}

	fileData.Clear();
    return true;
}

unsigned int src::Shader::GetShader(void) const noexcept
{
	return m_shader;
}

src::EShaderType src::Shader::GetShaderType(void) const noexcept
{
	return m_shaderType;
}

src::EShaderType src::Shader::ShaderType(const char* fileName) const
{
	size_t pos = std::string(fileName).rfind('.');

	if (pos == std::string::npos)
	{
		std::printf("Failed to process shader. Shader file does not have an extension.\n");
		return EShaderType::INVALID_SHADER;
	}
	
	switch (fileName[pos + 1])
	{
	case 'v':
		return EShaderType::VERTEX_SHADER;
	case 'f':
		return EShaderType::FRAGMENT_SHADER;
	case 'g':
		return EShaderType::GEOMETRY_SHADER;
	default:
		return EShaderType::INVALID_SHADER;
	}
}
