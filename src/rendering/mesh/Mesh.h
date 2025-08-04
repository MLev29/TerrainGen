#pragma once

#include "LibMath/vector/Vector2.h"
#include "LibMath/vector/Vector3.h"

#include <vector>

namespace src
{
	class Grid
	{
	public:
		Grid(void) = delete;
		Grid(math::Vector2<float> minPos, math::Vector2<float> maxPos, unsigned int divCount);
		~Grid(void);

		void Update(void);
	
	private:
		std::vector<struct Vertex> GridVertices(math::Vector3<float> v0, math::Vector3<float> v1, math::Vector3<float> v2, math::Vector3<float> v3, unsigned int div);
		std::vector<int> GridIndices(unsigned int div);

		void SetAttribute(unsigned int& index, int size, unsigned int& offset) const;
		void SetData(std::vector<math::Vector3<float>>& vertices, std::vector<int>& indices);
		void SetData(std::vector<Vertex>& vertices, std::vector<int>& indices);

		unsigned int m_vao;
		unsigned int m_indexCount;
	};
}