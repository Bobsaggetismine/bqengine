#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "bq/graphics/window.hpp"

void bq::window::initGlfw()
{
	//initialized glfw
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw" << std::endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
 	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	glewExperimental = true; // Needed for core profile
	glewInit();
}

bq::window::window(): m_Width(720), m_Height(1280), m_Title("bq_engine game"), m_Vsync(false)
{
	initGlfw();
}
bq::window::window(unsigned width, unsigned height, const std::string& title): m_Width(width), m_Height(height), m_Title(title), m_Vsync(false)
{
	initGlfw();
}
bq::window::window(unsigned width, unsigned height, const std::string& title, bool vsync) : m_Width(width), m_Height(height), m_Title(title), m_Vsync(vsync)
{
	initGlfw();
}

void bq::window::render()
{ 
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool bq::window::shouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

bq::window::~window() {
	glfwTerminate();
}

