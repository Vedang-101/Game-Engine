#pragma once

#include "../utils/logger.h"
#include "../utils/imageload.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "font/fontmanager.h"

namespace rse {
	namespace graphics {

		class Window {
		private:
			friend struct GLFWwindow;
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			
			bool m_Closed;
		public:
			Window(const char *title, int width, int height);
			Window(const char *title);
			~Window();
			void setBackground(unsigned int color) const;
			void setWindowIcon(const std::string& filename) const;
			void clear() const;
			void update();
			void close() const;
			bool closed() const;

			int getWidth() const { return m_Width; };
			int getHeight() const { return m_Height; };
		private:
			bool init(bool fullScreen = false);
			friend static void window_resize(GLFWwindow *window, int width, int height);
		};
	}
}