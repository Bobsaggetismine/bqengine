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



bq::gl_renderer_2d::gl_renderer_2d(glm::mat4x4* camera): m_default_shader("res/shaders/basic_shader.shader"),m_camera(camera) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void bq::gl_renderer_2d::set_quad_vertices(const glm::vec2& pos, const glm::vec2& size) {
    m_quad_vertices[0] = pos.x;
    m_quad_vertices[1] = pos.y;
    m_quad_vertices[4] = pos.x;
    m_quad_vertices[5] = pos.y + size.y;
    m_quad_vertices[8] = pos.x + size.x;
    m_quad_vertices[9] = pos.y + size.y;
    m_quad_vertices[12] = pos.x + size.x;
    m_quad_vertices[13] = pos.y;
}

void bq::gl_renderer_2d::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void bq::gl_renderer_2d::render(const bq::texture& tx, const bq::vertex_array& va, const bq::index_buffer& ib)
{
    tx.bind();
    m_default_shader.set_uniform_1i("u_Texture", 0);
    m_default_shader.set_uniform_mat4f("u_MVP", *m_camera);
    m_default_shader.bind();
    
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
}

void bq::gl_renderer_2d::render_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture) {
    
    set_quad_vertices(pos, size);


    bq::vertex_array va;
    bq::vertex_buffer vb(m_quad_vertices, 4 * 4 * sizeof(float));
    bq::index_buffer ib(m_default_quad_indices, 6);

    bq::vertex_buffer_layout layout;
    layout.add_float(2);
    layout.add_float(2);
    va.add_buffer(vb, layout);

    render(texture, va, ib);
}