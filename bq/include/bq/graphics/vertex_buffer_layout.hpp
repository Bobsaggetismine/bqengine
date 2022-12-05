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

    class BQ_API vertex_buffer_layout
    {
        unsigned int m_Stride;
        std::vector<bq::vertex_buffer_element> m_Elements;


        void push(unsigned int type, unsigned int count, unsigned char normalized);
    public:
        vertex_buffer_layout() : m_Stride(0) { }

        void add_float(unsigned int count);
        void add_unint(unsigned int count);
        void add_ubyte(unsigned int count);

        inline const std::vector<vertex_buffer_element> elements() const { return m_Elements; };
        inline unsigned int stride() const { return m_Stride; };
   
    };
}