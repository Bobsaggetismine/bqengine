#pragma once

#include "core.hpp"


namespace bq {
	class window {
	private:

		glm::mat4x4 m_camera;
		bq::gl_renderer_2d m_renderer;

		unsigned m_width, m_height;
		std::string m_Title;
		GLFWwindow* m_window;
		std::function<void(int, int)> m_event_callback_function;

		static bq::window* m_instance;

		void init();

		window(unsigned width, unsigned height, const std::string& title);

	public:

		//meh singleton
		static bq::window& instance()
		{
			assert(m_instance);
			return *m_instance;
		}
		static void create(unsigned width = 1280, unsigned height = 720, const std::string& title = "bqenine app")
		{
			assert(!m_instance);
			m_instance = new bq::window(width, height, title);
		}
		static void destroy()
		{
			assert(m_instance);
			delete m_instance;
		}

		~window();

		void render();
		void handle_key_input(GLFWwindow* window, int key, int scancode, int action, int mods);
		void handle_events();
		void set_event_callback(std::function<void(int, int)> func);
		bool should_close();

		inline unsigned width() const { return m_width; }
		inline unsigned height() const { return m_height; }
		inline const std::string& title() const { return m_Title; }
		bq::gl_renderer_2d& renderer() { return m_renderer; }


	};
}