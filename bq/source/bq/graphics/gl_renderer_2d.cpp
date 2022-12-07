#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "bq/graphics/texture.hpp"
#include "bq/graphics/index_buffer.hpp"
#include "bq/graphics/vertex_buffer.hpp"
#include "bq/graphics/vertex_buffer_layout.hpp"
#include "bq/graphics/vertex_array.hpp"
#include "bq/graphics/shader.hpp"
#include "bq/graphics/gl_renderer_2d.hpp"



bq::gl_renderer_2d::gl_renderer_2d(float width, float height) : m_projection(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), m_current_texture_id(0), m_default_shader(nullptr), m_camera(0.0f) {}

bq::gl_renderer_2d::~gl_renderer_2d() {}

void bq::gl_renderer_2d::init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int texcoords[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
    m_default_shader = std::make_unique<bq::shader>("res/shaders/basic_shader.shader");
    m_default_shader->set_uniform_1iv("u_Textures", 32, texcoords);
}

void bq::gl_renderer_2d::begin_batch()
{
    clear();
}
void bq::gl_renderer_2d::end_batch()
{
    bq::vertex_array va;
    bq::vertex_buffer vb(m_quad_vertices.data(), unsigned(m_quad_vertices.size() * sizeof(float)));
    bq::index_buffer ib(m_quad_indices.data(), unsigned(m_quad_indices.size()));

    bq::vertex_buffer_layout layout;
    layout.add_float(2);
    layout.add_float(2);
    layout.add_float(1);
    va.add_buffer(vb, layout);

    render(va, ib);

    m_quad_vertices.clear();
    m_quad_indices.clear();
    m_current_texture_id = 0;
}
void bq::gl_renderer_2d::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void bq::gl_renderer_2d::render_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture) {
    
    add_quad(pos, size, texture);
}


void bq::gl_renderer_2d::render(const bq::vertex_array& va, const bq::index_buffer& ib)
{
    ib.bind();
    va.bind();

    m_default_shader->bind();
    
    auto result = m_projection*(glm::translate(glm::mat4(1.0f), m_camera));

    m_default_shader->set_uniform_mat4f("u_MVP", result);
    
    glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}
void bq::gl_renderer_2d::move_camera(float x, float y)
{
    m_camera.x += x;
    m_camera.y += y;
}
void bq::gl_renderer_2d::add_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture)
{
    texture.bind((unsigned)m_current_texture_id);
    unsigned current_size = unsigned(m_quad_vertices.size() / 5);
    
    m_quad_vertices.insert(m_quad_vertices.end(), { pos.x,          pos.y,            0.0f, 0.0f, m_current_texture_id });
    m_quad_vertices.insert(m_quad_vertices.end(), { pos.x,          pos.y + size.y,   0.0f, 1.0f, m_current_texture_id });
    m_quad_vertices.insert(m_quad_vertices.end(), { pos.x + size.x, pos.y + size.y,   1.0f, 1.0f, m_current_texture_id });
    m_quad_vertices.insert(m_quad_vertices.end(), { pos.x + size.x, pos.y,            1.0f, 0.0f, m_current_texture_id });
    
    m_quad_indices.insert(m_quad_indices.end(), { 0 + current_size, 1 + current_size, 2 + current_size });
    m_quad_indices.insert(m_quad_indices.end(), { 2 + current_size, 3 + current_size, 0 + current_size });

    m_current_texture_id+=1;
}