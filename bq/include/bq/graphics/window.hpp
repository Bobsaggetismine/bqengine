#pragma once

#include "core.hpp"


namespace bq {
	class BQ_API window {
	private:
		unsigned m_Width, m_Height;
		std::string m_Title;
		bool m_Vsync;
		GLFWwindow* m_Window;

		void initGlfw();

	public:
		window();
		~window();

		window(unsigned width, unsigned height, const std::string& title);
		window(unsigned width, unsigned height, const std::string& title, bool vsync);


		void render();
		bool shouldClose();

		inline bool vsync() const { return m_Vsync; }
		inline unsigned width() const  { return m_Width; }
		inline unsigned height() const { return m_Height; }
		inline const std::string& title() const { return m_Title; }
		


	};
}