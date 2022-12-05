#pragma once
#include "core.hpp"

namespace bq {

    class BQ_API texture
    {
    private:
        unsigned int m_id;

        std::string m_filePath;
        int m_width, m_height, m_bitsPerPixel;

    public:
        texture(const std::string& path);
        ~texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int width() const { return m_width; }
        inline int height() const { return m_height; }
    };
}