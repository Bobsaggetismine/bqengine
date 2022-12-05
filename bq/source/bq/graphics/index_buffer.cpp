#include <GL/glew.h>

#include "bq/graphics/index_buffer.hpp"

bq::index_buffer::index_buffer(const unsigned* data, unsigned count): m_count(count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW);
}

bq::index_buffer::~index_buffer()
{
	glDeleteBuffers(1, &m_id);
}

void bq::index_buffer::bind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void bq::index_buffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}