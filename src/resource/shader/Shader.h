#pragma once

#include "resource/Resource.h"

#include "LibMath/vector/Vector2.h"
#include "LibMath/vector/Vector3.h"
#include "LibMath/vector/Vector4.h"
#include "LibMath/matrix/Matrix2.h"
#include "LibMath/matrix/Matrix3.h"
#include "LibMath/matrix/Matrix4.h"

#include <string>

namespace src
{
	class ShaderProgram final : public IResource
	{
	public:
		ShaderProgram(void) = default;
		ShaderProgram(const char* vertexShader, const char* fragShader);
		virtual ~ShaderProgram(void) override = default;

		bool LoadResource(const char* filePath) override;

		void Use(void) const;

		// Scalar types
		void Set(const char* uniformName, bool value) const;
		void Set(const char* uniformName, int value) const;
		void Set(const char* uniformName, unsigned int value) const;
		void Set(const char* uniformName, float value) const;
		void Set(const char* uniformName, double value) const;

		// Vectors
		void Set(const char* uniformName, math::Vector2<int> const& vec) const;
		void Set(const char* uniformName, math::Vector3<int> const& vec) const;
		void Set(const char* uniformName, math::Vector4<int> const& vec) const;

		void Set(const char* uniformName, math::Vector2<float> const& vec) const;
		void Set(const char* uniformName, math::Vector3<float> const& vec) const;
		void Set(const char* uniformName, math::Vector4<float> const& vec) const;

		void Set(const char* uniformName, math::Vector2<double> const& vec) const;
		void Set(const char* uniformName, math::Vector3<double> const& vec) const;
		void Set(const char* uniformName, math::Vector4<double> const& vec) const;

		// Matrices
		void Set(const char* uniformName, const math::Matrix2<float>* matrix) const;
		void Set(const char* uniformName, const math::Matrix3<float>* matrix) const;
		void Set(const char* uniformName, const math::Matrix4<float>* matrix) const;

		void Set(const char* uniformName, const math::Matrix2<double>* matrix) const;
		void Set(const char* uniformName, const math::Matrix3<double>* matrix) const;
		void Set(const char* uniformName, const math::Matrix4<double>* matrix) const;


        const std::string& GetVertexShaderName(void) const;
        const std::string& GetFragmentShaderName(void) const;

	private:
		void CreateProgram(void);

		std::string m_vertexShader;
		std::string m_fragShader;
		
		unsigned int m_programID = 0;

        friend class ResourceManager;
	};
}