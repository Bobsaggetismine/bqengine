#include <GL/glew.h>

#include <vector>

#include "bq/graphics/vertex_buffer_layout.hpp"
#include "bq/graphics/vertex_buffer.hpp"
#include "bq/graphics/vertex_array.hpp"

bq::vertex_array::vertex_array()
{
    glGenVertexArrays(1, &m_RendererID);
}
bq::vertex_array::~vertex_array()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
void bq::vertex_array::add_buffer(const vertex_buffer& vb, const bq::vertex_buffer_layout& layout)
{
    bind();
    vb.bind();
    const std::vector<vertex_buffer_element> elements = layout.elements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const vertex_buffer_element element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized,layout.stride(), (void*)(uintptr_t)(offset));
        offset += element.count * vertex_buffer_element::get_size_of_type(element.type);
    }
}
void bq::vertex_array::bind() const
{
    glBindVertexArray(m_RendererID);
}
void bq::vertex_array::unbind() const
{
    glBindVertexArray(0);
};