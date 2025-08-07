#include "Grid.h"
#include "utility/Buffer.h"
#include "rendering/mesh/Vertex.h"
#include "utility/PerlinNoise.h"

#include "glad/glad.h"

src::Grid::Grid(math::Vector2<float> minPos, math::Vector2<float> maxPos, unsigned int divCount)
	: m_vao(0), m_indexCount(0)
{
	// Calculate data for each vertex in grid for VBO buffer
	std::vector<Vertex> vertices = GridVertices(
		{minPos[0], 0.0f, minPos[1]}, // bottom left grid corner
		{maxPos[0], 0.0f, minPos[1]}, // bottom right grid corner
		{maxPos[0], 0.0f, maxPos[1]}, // top right grid corner
		{minPos[0], 0.0f, maxPos[1]}, // top left grid corner
		divCount // number of times to divide grid (for interior vertices)
	);

	// Calculate data for indices for EBO buffer
	std::vector<int> indices = GridIndices(divCount);

	// Store index count for updating rendering
	m_indexCount = static_cast<unsigned int>(indices.size());
	
	// Send data to GPU
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
	// Draw grid with tessellation
	glBindVertexArray(m_vao); // Bind vertex array
	glDrawElements(GL_PATCHES, m_indexCount, GL_UNSIGNED_INT, 0); // Draw
	glBindVertexArray(0); // Unbind vertex array
}

std::vector<src::Vertex> src::Grid::GridVertices(math::Vector3<float> v0, math::Vector3<float> v1, math::Vector3<float> v2, math::Vector3<float> v3, unsigned int div)
{
	// Array containing vertex data for plane
	std::vector<Vertex> vertices;

	const float divDenom = 1.0f / static_cast<float>(div);

	math::Vector3<float> vec03 = (v3 - v0) * divDenom;
	math::Vector3<float> vec12 = (v2 - v1) * divDenom;

	// Iterate through each row
	for (unsigned int row = 0; row < div + 1; ++row)
	{
		math::Vector3<float> start = v0 + vec03 * row;
		math::Vector3<float> end = v1 + vec12 * row;

		math::Vector3<float> vecDiv = (end - start) * divDenom;

		// Iterate through each column
		for (unsigned int col = 0; col < div + 1; ++col)
		{
			// Vertex position
			math::Vector3<float> currPos = start + vecDiv * static_cast<float>(col);

			float val = 0.0f;
			float amplitude = 1.0f;
			float frequency = 1.0f;

			for (int i = 0; i < 12; ++i)
			{
				val += PerlinNoise(currPos[0] * frequency * divDenom, currPos[2] * frequency * divDenom) * amplitude;
				//frequency *= 2.0f;
				//amplitude /= 2.0f;
			}

			val *= 1.2f * 1.f;

			//currPos[1] = val;

			// Texture coord (UVs)
			math::Vector2<float> texCoord(
				static_cast<float>(col) * divDenom,
				static_cast<float>(row) * divDenom
			);

			// Add vertex position and texture coordinate data to array 
			vertices.push_back(Vertex(currPos, texCoord, {}, {}, {}));
		}
	}

	return vertices;
}

std::vector<int> src::Grid::GridIndices(unsigned int div)
{
	std::vector<int> indices;

	// Iterate through each row
	for (unsigned int row = 0; row < div; ++row)
	{
		// Iterate through each column
		for (unsigned int col = 0; col < div; ++col)
		{
			// For each point in vertex add it to index array
			int index = row * (div + 1) + col;

			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + (div + 1) + 1);
			indices.push_back(index + (div + 1));
		}
	}

	return indices;
}

void src::Grid::SetAttribute(unsigned int& index, int size, unsigned int& offset) const
{
	glEnableVertexArrayAttrib(m_vao, index);
	glVertexArrayAttribBinding(m_vao, index, 0);
	glVertexArrayAttribFormat(m_vao, index, size, GL_FLOAT, GL_FALSE, offset);

	++index;
	offset += size * sizeof(float);
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
	unsigned int index = 0;
	unsigned int offset = 0;

	SetAttribute(index, 3, offset); // Position attribute
	SetAttribute(index, 3, offset); // Normal attribute
	SetAttribute(index, 3, offset); // Tangent attribute
	SetAttribute(index, 3, offset); // Bi - tangent attribute
	SetAttribute(index, 2, offset); // Texture coord. attribute

	glVertexArrayElementBuffer(m_vao, ebo);
	glVertexArrayVertexBuffer(m_vao, 0, vbo, 0, offset);
}