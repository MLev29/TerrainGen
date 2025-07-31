#include "Mesh.h"
#include "utility/Buffer.h"
#include "rendering/mesh/Vertex.h"

#include "glad/glad.h"

src::Grid::Grid(math::Vector2<float> minPos, math::Vector2<float> maxPos, unsigned int divCount)
	: m_vao(0), m_indexCount(0)
{
	std::vector<Vertex> vertices = GridVerticesWithAttributes(
		{minPos[0], 0.0f, minPos[1]},
		{maxPos[0], 0.0f, minPos[1]},
		{maxPos[0], 0.0f, maxPos[1]},
		{minPos[0], 0.0f, maxPos[1]},
		divCount
	);

	std::vector<int> indices = GridTesIndices(divCount);

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
	glDrawElements(GL_PATCHES, m_indexCount, GL_UNSIGNED_INT, 0);
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

std::vector<src::Vertex> src::Grid::GridVerticesWithAttributes(math::Vector3<float> v0, math::Vector3<float> v1, math::Vector3<float> v2, math::Vector3<float> v3, unsigned int div)
{
	// Array containing vertex data for plane
	std::vector<Vertex> vertices;

	const float divDenom = 1.0f / static_cast<float>(div);

	math::Vector3<float> vec03 = (v3 - v0) * divDenom;
	math::Vector3<float> vec12 = (v2 - v1) * divDenom;

	for (unsigned int row = 0; row < div + 1; ++row)
	{
		math::Vector3<float> start = v0 + vec03 * row;
		math::Vector3<float> end = v1 + vec12 * row;

		math::Vector3<float> vecDiv = (end - start) * divDenom;

		for (unsigned int col = 0; col < div + 1; ++col)
		{
			// Vertex position
			math::Vector3<float> currVec = start + vecDiv * static_cast<float>(col);
			currVec[1] += (fmodf((float) std::rand(), 20.0f)) - 10.f;

			// Texture coord (UVs)
			math::Vector2<float> texCoord(
				static_cast<float>(col) * divDenom, 
				static_cast<float>(row) * divDenom
			);

			// Tangent space vectors (tangent & bi - tangent)
			math::Vector3<float> vecDivCopy = vecDiv;
			math::Vector3<float> tangent = vecDivCopy.Normalize();

			math::Vector3<float> nextStart = start + vec03;
			math::Vector3<float> nextEnd = end + vec12;
			math::Vector3<float> nextVectorDiv = (nextEnd - nextStart) * divDenom;
			math::Vector3<float> nextRowCurrVec = nextStart + nextVectorDiv * static_cast<float>(col);
			math::Vector3<float> possibleBiTangent = (nextRowCurrVec - currVec).Normalize();

			// Normal
			math::Vector3<float> normal = tangent.Cross(possibleBiTangent);

			Vertex newVertex(currVec, texCoord, normal, tangent, possibleBiTangent);
			vertices.push_back(newVertex);
		}
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

std::vector<int> src::Grid::GridTesIndices(unsigned int div)
{
	std::vector<int> indices;

	for (unsigned int row = 0; row < div; ++row)
	{
		for (unsigned int col = 0; col < div; ++col)
		{
			int index = row * (div + 1) + col;

			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + (div + 1) + 1);
			indices.push_back(index + (div + 1));
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
	vbo.SetData(vertices.data(), sizeof(Vertex) * vertices.size());
	ebo.SetData(indices.data(), sizeof(int) * indices.size());

	// Set attributes
	SetAttribute(0, 3, 0); // Position attribute
	SetAttribute(1, 3, 3); // Normal attribute
	SetAttribute(2, 3, 6); // Tangent attribute
	SetAttribute(3, 3, 9); // Bi - tangent attribute
	SetAttribute(4, 2, 12); // Texture coord attribute

	glVertexArrayVertexBuffer(m_vao, 0, vbo, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(m_vao, ebo);
}


void src::Grid::SetData(std::vector<Vertex>& vertices, std::vector<int>& indices)
{
	// Create buffers
	glCreateVertexArrays(1, &m_vao);
	Buffer vbo, ebo;

	// Set data
	vbo.SetData(vertices.data(), sizeof(Vertex) * vertices.size());
	ebo.SetData(indices.data(), sizeof(int) * indices.size());

	// Set attributes
	SetAttribute(0, 3, 0); // Position attribute
	SetAttribute(1, 3, 3); // Normal attribute
	SetAttribute(2, 3, 6); // Tangent attribute
	SetAttribute(3, 3, 9); // Bi - tangent attribute
	SetAttribute(4, 2, 12); // Texture coord attribute

	glVertexArrayVertexBuffer(m_vao, 0, vbo, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(m_vao, ebo);
}