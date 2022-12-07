#include <GL/glew.h>
#include <stb_image.h>

#include <string>

#include "bq/graphics/texture.hpp"

bq::texture::texture(const std::string& path) : m_id(0), m_file_path(path), m_width(0), m_height(0), m_bits_per_pixel(0)
{
    stbi_set_flip_vertically_on_load(1);
    unsigned char* m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bits_per_pixel, 4);
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    unbind();

    if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
};
bq::texture::~texture()
{
    glDeleteTextures(1, &m_id);
}
void bq::texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
void bq::texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}