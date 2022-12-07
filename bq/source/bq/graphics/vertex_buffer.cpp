#include <GL/glew.h>

#include "bq/graphics/vertex_buffer.hpp"

bq::vertex_buffer::vertex_buffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
bq::vertex_buffer::~vertex_buffer()
{
    glDeleteBuffers(1, &m_id);
}
void bq::vertex_buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
void bq::vertex_buffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}