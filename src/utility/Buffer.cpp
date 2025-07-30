#include "Buffer.h"

#include "glad/glad.h"

src::Buffer::Buffer(void)
{
	glCreateBuffers(1, &m_buffer);
}

src::Buffer::~Buffer(void)
{
	glDeleteBuffers(1, &m_buffer);
	m_buffer = 0;
}

void src::Buffer::SetData(void* data, size_t size)
{
	glNamedBufferData(m_buffer, size, data, GL_STATIC_DRAW);
}

void src::Buffer::SetData(void* data, size_t size, unsigned int offset)
{
	glNamedBufferSubData(m_buffer, offset, size, data);
}

void src::Buffer::DeleteData(void)
{
	glDeleteBuffers(1, &m_buffer);
	m_buffer = 0;
}

src::Buffer::operator unsigned int(void) const noexcept
{
	return m_buffer;
}
