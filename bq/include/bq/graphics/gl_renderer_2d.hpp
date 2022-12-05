#pragma once

#include "core.hpp"



namespace bq {
    class gl_renderer_2d
    {

        unsigned m_default_quad_indices[6] = {
           0,1,2,
           0,2,3
        };
        float m_quad_vertices[4 * 4] = {
                0.0f,0.0f, 0.0f, 0.0f,
                0.0f,0.0f, 0.0f, 1.0f,
                0.0f,0.0f, 1.0f, 1.0f,
                0.0f,0.0f, 1.0f, 0.0f
        };

        glm::mat4x4* m_camera;
        bq::shader m_default_shader;

        void set_quad_vertices(const glm::vec2& pos, const glm::vec2& size);
        void render(const bq::texture& tx, const bq::vertex_array& va, const bq::index_buffer& ib);

    public:

        gl_renderer_2d(glm::mat4x4* camera);

        void clear() const;
        void render_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture);

    };
}