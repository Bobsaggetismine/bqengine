#pragma once
#include "core.hpp"

namespace bq {

    class BQ_API vertex_array
    {
    private:
        unsigned int m_id;

    public:
        vertex_array();
        ~vertex_array();

        void add_buffer(const vertex_buffer& vb, const bq::vertex_buffer_layout& layout);
        void bind() const;
        void unbind() const;

    };
}