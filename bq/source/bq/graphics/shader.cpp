#include <glm.hpp>
#include <GL/glew.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "bq/graphics/shader.hpp"

bq::shader::shader(const std::string& filepath) : m_file_path(filepath), m_id(0)
{
    shader_program_source source = parse_shader(filepath);


    m_id = create_shader(source.vertex_source, source.fragment_source);

    glUseProgram(m_id);
}

bq::shader::~shader()
{
    glDeleteProgram(m_id);
}

void bq::shader::bind() const
{
    glUseProgram(m_id);
}

void bq::shader::unbind() const
{
    glUseProgram(0);
}

void bq::shader::set_uniform_1i(const std::string& name, int value)
{
    glUniform1i(get_uniform_location(name), value);
}
void bq::shader::set_uniform_1iv(const std::string& name, int size, int* values)
{
    glUniform1iv(get_uniform_location(name), size, values);
}
void bq::shader::set_uniform_1f(const std::string& name, float value)
{
    glUniform1f(get_uniform_location(name), value);
}
void bq::shader::set_uniform_4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    glUniform4f(get_uniform_location(name), f0, f1, f2, f3);
}
void bq::shader::set_uniform_mat4f(const std::string& name, const glm::mat4& mtx)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mtx[0][0]);
}

int bq::shader::get_uniform_location(const std::string& name)
{
    if (m_uniform_cache.find(name) != m_uniform_cache.end())
        return m_uniform_cache[name];

    int location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1)
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;

    m_uniform_cache[name] = location;

    return location;
}
bq::shader_program_source bq::shader::parse_shader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    shader_type type = NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    struct shader_program_source sps = { ss[0].str(), ss[1].str() };
    return sps;
}

unsigned int bq::shader::compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout
            << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader"
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int bq::shader::create_shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    GLint program_linked;

    glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}