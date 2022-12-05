#pragma once
#include "core.hpp"

namespace bq {

    enum shader_type
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    struct shader_program_source
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class shader
    {
    private:
        unsigned int m_id;
        std::string m_filePath;
        std::unordered_map<std::string, int> m_uniformCache;

    public:
        shader(const std::string& filepath);
        ~shader();

        void bind() const;
        void unbind() const;


        void set_uniform_1i(const std::string& name, int value);
        void set_uniform_1f(const std::string& name, float value);
        void set_uniform_1iv(const std::string& name, int size, int* value);
        void set_uniform_4f(const std::string& name, float f0, float f1, float f2, float f3);
        void set_uniform_mat4f(const std::string& name, const glm::mat4& mtx);

    private:
        int                      get_uniform_location(const std::string& name);
        shader_program_source    parse_shader(const std::string& filepath);
        unsigned int             compile_shader(unsigned int type, const std::string& source);
        unsigned int             create_shader(const std::string& vertexShader, const std::string& fragmentShader);


    };
}