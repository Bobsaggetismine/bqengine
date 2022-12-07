#include <GL/glew.h>

#include <vector>
#include <iostream>

#include "bq/graphics/vertex_buffer_layout.hpp"


unsigned int bq::vertex_buffer_element::get_size_of_type(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT: return sizeof(GLfloat);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
    }
    return 0;
}

void bq::vertex_buffer_layout::add_float(unsigned count) { push(GL_FLOAT, count, GL_FALSE); }
void bq::vertex_buffer_layout::add_unint(unsigned count) { push(GL_UNSIGNED_INT, count, GL_FALSE); }
void bq::vertex_buffer_layout::add_ubyte(unsigned count) { push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

void bq::vertex_buffer_layout::push(unsigned int type, unsigned int count, unsigned char normalized)
{
    vertex_buffer_element vbe = { type, count, normalized };
    //std::cout << vbe.count << " : " << vbe.normalized << " : " << vbe.type << std::endl;
    m_elements.push_back(vbe);
    m_stride += count * vertex_buffer_element::get_size_of_type(type);
};