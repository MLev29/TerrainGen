#include "Mesh.h"
#include "utility/Buffer.h"

#include "glad/glad.h"

src::Grid::Grid(math::Vector2<float> minPos, math::Vector2<float> maxPos, unsigned int divCount)
	: m_vao(0), m_indexCount(0)
{
	std::vector<math::Vector3<float>> vertices = GridVertices(
		{minPos[0], 0.0f, minPos[1]},
		{maxPos[0], 0.0f, minPos[1]},
		{maxPos[0], 0.0f, maxPos[1]},
		{minPos[0], 0.0f, maxPos[1]},
		divCount
	);

	std::vector<int> indices = GridIndices(divCount);

	m_indexCount = static_cast<unsigned int>(indices.size());
	SetData(vertices, indices);
}

src::Grid::~Grid(void)
{
	glDeleteVertexArrays(1, &m_vao);

	m_vao = 0;
	m_indexCount = 0;
}

void src::Grid::Update(void)
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<math::Vector3<float>> src::Grid::GridVertices(math::Vector3<float> v0, math::Vector3<float> v1, math::Vector3<float> v2, math::Vector3<float> v3, unsigned int div)
{
	// Array containing vertex data for plane
	std::vector<math::Vector3<float>> vertices;

	math::Vector3<float> vec03 = (v3 - v0) / div;
	math::Vector3<float> vec12 = (v2 - v1) / div;

	for (unsigned int row = 0; row < div + 1; ++row)
	{
		math::Vector3<float> start = v0 + vec03 * row;
		math::Vector3<float> end = v1 + vec12 * row;

		std::vector<math::Vector3<float>> lineVertices = Line(start, end, div);

		vertices.insert(vertices.end(), lineVertices.begin(), lineVertices.end());
	}

	return vertices;
}

std::vector<int> src::Grid::GridIndices(unsigned int div)
{
	std::vector<int> indices;

	for (unsigned int row = 0; row < div; ++row)
	{
		for (unsigned int col = 0; col < div; ++col)
		{
			int index = row * (div + 1) + col;

			indices.push_back(index);
			indices.push_back(index + (div + 1) + 1);
			indices.push_back(index + (div + 1));

			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + (div + 1) + 1);
		}
	}

	return indices;
}

std::vector<math::Vector3<float>> src::Grid::Line(math::Vector3<float> start, math::Vector3<float> end, int div)
{
	std::vector<math::Vector3<float>> line;

	math::Vector3<float> vectorDiv = (end - start) / div;

	for (int i = 0; i < div + 1; ++i)
	{
		math::Vector3<float> vertex = start + (vectorDiv * float(i));
		line.push_back(vertex);
	}

	return line;
}

void src::Grid::SetAttribute(unsigned int index, int size, unsigned int offset) const
{
	glEnableVertexArrayAttrib(m_vao, index);
	glVertexArrayAttribBinding(m_vao, index, 0);
	glVertexArrayAttribFormat(m_vao, index, size, GL_FLOAT, GL_FALSE, offset);
}

void src::Grid::SetData(std::vector<math::Vector3<float>>& vertices, std::vector<int>& indices)
{
	// Create buffers
	glCreateVertexArrays(1, &m_vao);
	Buffer vbo, ebo;
	
	// Set data
	vbo.SetData(vertices.data(), sizeof(math::Vector3<float>) * vertices.size());
	ebo.SetData(indices.data(), sizeof(int) * indices.size());

	// Set attributes
	SetAttribute(0, 3, 0); // Position attibute

	glVertexArrayVertexBuffer(m_vao, 0, vbo, 0, 3 * sizeof(float));
	glVertexArrayElementBuffer(m_vao, ebo);
}
