#include "resource/shader/Shader.h"
#include "resource/shader/ShaderResource.h"
#include "resource/ResourceManager.h"

#include "glad/glad.h"

src::ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragShader)
	: m_vertexShader(vertexShader), m_fragShader(fragShader), m_programID(0)
{
	CreateProgram();
}

src::ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragShader, const char* tesControlShader, const char* tesEvalShader)
	: m_vertexShader(vertexShader), m_fragShader(fragShader), m_tesCtrlShader(tesControlShader), m_tesEvalShader(tesEvalShader), m_programID(0)
{
	CreateTessellationProgram();
}

src::ShaderProgram::~ShaderProgram(void)
{
	glDeleteProgram(m_programID);
}

bool src::ShaderProgram::LoadResource(const char* filePath)
{
	(void) filePath;
    return true;
}

void src::ShaderProgram::Use(void) const
{
	return glUseProgram(m_programID);
}

// Scalar types
void src::ShaderProgram::Set(const char* uniformName, bool value) const
{
	glUniform1i(glGetUniformLocation(m_programID, uniformName), value);
}

void src::ShaderProgram::Set(const char* uniformName, int value) const
{
	glUniform1i(glGetUniformLocation(m_programID, uniformName), value);
}

void src::ShaderProgram::Set(const char* uniformName, unsigned int value) const
{
	glUniform1ui(glGetUniformLocation(m_programID, uniformName), value);
}

void src::ShaderProgram::Set(const char* uniformName, float value) const
{
	glUniform1f(glGetUniformLocation(m_programID, uniformName), value);
}
 
void src::ShaderProgram::Set(const char* uniformName, double value) const
{
	glUniform1d(glGetUniformLocation(m_programID, uniformName), value);
}

// Vector ints
void src::ShaderProgram::Set(const char* uniformName, math::Vector2<int> const& vec) const
{
	glUniform2i(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector3<int> const& vec) const
{
	glUniform3i(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector4<int> const& vec) const
{
	glUniform4i(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2], vec[3]);
}

// Vector floats
void src::ShaderProgram::Set(const char* uniformName, math::Vector2<float> const& vec) const
{
	glUniform2f(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector3<float> const& vec) const
{
	glUniform3f(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector4<float> const& vec) const
{
	glUniform4f(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2], vec[3]);
}

// Vector double
void src::ShaderProgram::Set(const char* uniformName, math::Vector2<double> const& vec) const
{
	glUniform2d(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector3<double> const& vec) const
{
	glUniform3d(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2]);
}

void src::ShaderProgram::Set(const char* uniformName, math::Vector4<double> const& vec) const
{
	glUniform4d(glGetUniformLocation(m_programID, uniformName), vec[0], vec[1], vec[2], vec[3]);
}

// Matrix float
void src::ShaderProgram::Set(const char* uniformName, const math::Matrix2<float>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix2fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(matrix));
}

void src::ShaderProgram::Set(const char* uniformName, const math::Matrix3<float>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(matrix));
}

void src::ShaderProgram::Set(const char* uniformName, const math::Matrix4<float>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(matrix));
}

// Matrix double
void src::ShaderProgram::Set(const char* uniformName, const math::Matrix2<double>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix2dv(location, 1, GL_FALSE, reinterpret_cast<const double*>(matrix));
}

void src::ShaderProgram::Set(const char* uniformName, const math::Matrix3<double>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix3dv(location, 1, GL_FALSE, reinterpret_cast<const double*>(matrix));
}

void src::ShaderProgram::Set(const char* uniformName, const math::Matrix4<double>* matrix) const
{
	int location = glGetUniformLocation(m_programID, uniformName);

	glUniformMatrix4dv(location, 1, GL_FALSE, reinterpret_cast<const double*>(matrix));
}

const std::string& src::ShaderProgram::GetVertexShaderName(void) const
{
    return m_vertexShader;
}

const std::string& src::ShaderProgram::GetFragmentShaderName(void) const
{
    return m_fragShader;
}

void src::ShaderProgram::CreateProgram(void)
{
    // Don't create OpenGL program twice
    if (m_programID)
        return;
     
	// Resource manager will only load if resource does not exist
	Shader* vShader = ResourceManager::Load<Shader>(m_vertexShader);
	Shader* fShader = ResourceManager::Load<Shader>(m_fragShader);

    if (!vShader || !fShader)
    {
        std::printf("Failed to compute shader.\n");
        return;
    }

	if (!vShader->GetShaderType() ||
		!fShader->GetShaderType())
	{
		std::printf("Failed to create shader program. Error: vertex or fragment shader error.\n");
		return;
	}
	
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vShader->GetShader());
	glAttachShader(m_programID, fShader->GetShader());
	glLinkProgram(m_programID);

	int result;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);

	if (!result)
	{
		constexpr int bufferSize = 2500;
		char infoLog[bufferSize];

		glGetProgramInfoLog(m_programID, bufferSize, nullptr, infoLog);
		std::printf("Failed to link shader program, reason: %s\n", infoLog);

		return;
	}

	glDeleteShader(vShader->GetShader());
	glDeleteShader(fShader->GetShader());
}

void src::ShaderProgram::CreateTessellationProgram(void)
{
	// Don't create OpenGL program twice
	if (m_programID)
		return;

	// Resource manager will only load if resource does not exist
	Shader* vShader = ResourceManager::Load<Shader>(m_vertexShader);
	Shader* fShader = ResourceManager::Load<Shader>(m_fragShader);
	Shader* tcShader = ResourceManager::Load<Shader>(m_tesCtrlShader);
	Shader* teShader = ResourceManager::Load<Shader>(m_tesEvalShader);

	if (!vShader || !fShader || !tcShader || !teShader)
	{
		std::printf("Failed to compute shader.\n");
		return;
	}

	if (!vShader->GetShaderType() ||
		!fShader->GetShaderType() ||
		!tcShader->GetShaderType() ||
		!teShader->GetShaderType())
	{
		std::printf("Failed to create shader program. Error: vertex or fragment or tessellation shader error.\n");
		return;
	}

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vShader->GetShader());
	glAttachShader(m_programID, fShader->GetShader());
	glAttachShader(m_programID, tcShader->GetShader());
	glAttachShader(m_programID, teShader->GetShader());
	glLinkProgram(m_programID);

	int result;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);

	if (!result)
	{
		constexpr int bufferSize = 2500;
		char infoLog[bufferSize];

		glGetProgramInfoLog(m_programID, bufferSize, nullptr, infoLog);
		std::printf("Failed to link shader program, reason: %s\n", infoLog);

		return;
	}

	glDeleteShader(vShader->GetShader());
	glDeleteShader(fShader->GetShader());
	glDeleteShader(tcShader->GetShader());
	glDeleteShader(teShader->GetShader());
}
