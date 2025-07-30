#pragma once

#include "resource/Resource.h"

namespace src
{
	enum EShaderType : unsigned short
	{
		INVALID_SHADER,
		VERTEX_SHADER = 0x8B31,
		FRAGMENT_SHADER = 0x8B30,
		GEOMETRY_SHADER = 0x8DD9
	};

	class Shader final : public IResource
	{
	public:
		Shader(void);
		~Shader(void) = default;

		bool LoadResource(const char* fileName) override;

		unsigned int GetShader(void) const noexcept;
		EShaderType GetShaderType(void) const noexcept;

	private:
		EShaderType ShaderType(const char* fileName) const;
		unsigned int m_shader;
		EShaderType m_shaderType;
	};
}