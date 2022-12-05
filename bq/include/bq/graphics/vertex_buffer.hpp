#pragma once
#include "core.hpp"

namespace bq {
    class BQ_API vertex_buffer
    {
    private:
        unsigned int m_RendererID;

    public:
        vertex_buffer(const void* data, unsigned int size);
        ~vertex_buffer();
        void bind() const;
        void unbind() const;
    };
}