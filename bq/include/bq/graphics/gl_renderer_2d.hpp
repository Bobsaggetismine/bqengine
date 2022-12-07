#pragma once

#include "core.hpp"



namespace bq {
    class gl_renderer_2d
    {
        float m_current_texture_id;

        std::vector<float>  m_quad_vertices;
        std::vector<unsigned> m_quad_indices;
        
        glm::mat4 m_projection;
        glm::vec3 m_camera = glm::vec3(0, 0, 0);

        std::unique_ptr<bq::shader> m_default_shader;
        
       

        void add_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture);
        void render(const bq::vertex_array& va, const bq::index_buffer& ib);

    public:

        gl_renderer_2d(float width, float height);
        ~gl_renderer_2d();
        void clear() const;
        void init();
        void begin_batch();
        void end_batch();
        void render_quad(const glm::vec2& pos, const glm::vec2& size, const bq::texture& texture);
        void move_camera(float x, float y);
    };
}