#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "bq/graphics/texture.hpp"
#include "bq/graphics/index_buffer.hpp"
#include "bq/graphics/vertex_buffer.hpp"
#include "bq/graphics/vertex_buffer_layout.hpp"
#include "bq/graphics/vertex_array.hpp"
#include "bq/graphics/shader.hpp"
#include "bq/graphics/gl_renderer_2d.hpp"
#include "bq/graphics/window.hpp"

bq::window* bq::window::m_instance = nullptr;

bq::window::window(unsigned width, unsigned height, const std::string& title) : m_width(width), m_height(height), m_Title(title), m_renderer(width, height)
{
	init();
	m_renderer.init();
}

bq::window::~window()
{
	glfwTerminate();
}

void bq::window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw" << std::endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(m_width, m_height, m_Title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glewExperimental = true; // Needed for core profile
	glewInit();

	auto func = [](GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		static_cast<bq::window*>(glfwGetWindowUserPointer(win))->handle_key_input(win, key, scancode, action, mods);
	};

	glfwSetKeyCallback(m_window, func);
}

void bq::window::set_event_callback(std::function<void(int, int)> func)
{
	m_event_callback_function = func;
}
void bq::window::handle_events()
{
	glfwPollEvents();
}
void bq::window::handle_key_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	bq::window::instance().m_event_callback_function(key, action);
}
bool bq::window::should_close()
{
	return glfwWindowShouldClose(m_window);
}

void bq::window::render()
{
	glfwSwapBuffers(m_window);
	
}
