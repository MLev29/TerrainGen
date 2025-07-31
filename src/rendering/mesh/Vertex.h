#pragma once

#include "LibMath/vector/Vector2.h"
#include "LibMath/vector/Vector3.h"

namespace src
{
	struct Vertex
	{
		math::Vector3<float> m_position;
		math::Vector3<float> m_normal;
		math::Vector3<float> m_tangent;
		math::Vector3<float> m_biTangent;
		math::Vector2<float> m_texCoord;

		Vertex(math::Vector3<float> position, math::Vector2<float> texCoord, math::Vector3<float> normal, math::Vector3<float> tangent, math::Vector3<float> biTangent)
			: m_position(position), m_texCoord(texCoord), m_normal(normal), m_tangent(tangent), m_biTangent(biTangent)
			{}

	};
}