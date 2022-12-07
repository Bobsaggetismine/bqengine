#pragma once
#include "core.hpp"

namespace bq {
    struct vertex_buffer_element
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int get_size_of_type(unsigned int type);
    };

    class vertex_buffer_layout
    {
        unsigned int m_stride;
        std::vector<bq::vertex_buffer_element> m_elements;


        void push(unsigned int type, unsigned int count, unsigned char normalized);
    public:
        vertex_buffer_layout() : m_stride(0) { }

        void add_float(unsigned count);
        void add_unint(unsigned count);
        void add_ubyte(unsigned count);

        inline const std::vector<vertex_buffer_element> elements() const { return m_elements; };
        inline unsigned int stride() const { return m_stride; };
   
    };
}