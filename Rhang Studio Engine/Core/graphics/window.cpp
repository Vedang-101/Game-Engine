#include "window.h"
#include "../input/desktop.h"

namespace rse {
	namespace graphics {
		void window_resize(GLFWwindow *window, int width, int height);

		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init())
				glfwTerminate();

			//Initialize Desktop Inputs
			for (int i = 0; i < MAX_KEYS; i++) {
				input::Desktop::m_Keys[i] = 0;
				input::Desktop::m_KeyState[i] = 0;
			}
			input::Desktop::m_MouseButtons = 0;
			input::Desktop::m_MouseButtonState = 0;
			input::Desktop::m_ScrollX = 0;
			input::Desktop::m_ScrollY = 0;
			input::Desktop::m_CursorVisible = true;
			input::Desktop::m_Window = m_Window;

			FontManager::add(new Font());
		}

		Window::Window(const char *title) {
			m_Title = title;
			if (!init(true))
				glfwTerminate();

			//Initialize Desktop Inputs
			for (int i = 0; i < MAX_KEYS; i++) {
				input::Desktop::m_Keys[i] = 0;
				input::Desktop::m_KeyState[i] = 0;
			}
			input::Desktop::m_MouseButtons = 0;
			input::Desktop::m_MouseButtonState = 0;
			input::Desktop::m_ScrollX = 0;
			input::Desktop::m_ScrollY = 0;
			input::Desktop::m_CursorVisible = true;
			input::Desktop::m_Window = m_Window;

			FontManager::add(new Font());
		}

		Window::~Window() {
			FontManager::clean();
			glfwTerminate();
		}

		bool Window::init(bool fullScreen) {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}
			if (fullScreen) {
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				m_Width = mode->width;
				m_Height = mode->height;

				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
			}
			else
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				rse::utils::LogError("Failed to create GLFW window");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);

			//Desktop Input Callbacks
			glfwSetKeyCallback(m_Window, input::Desktop::key_callback);
			glfwSetMouseButtonCallback(m_Window, input::Desktop::mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, input::Desktop::cursor_position_callback);
			glfwSetScrollCallback(m_Window, input::Desktop::scroll_callback);

			glfwSwapInterval(1);

			if (glewInit() != GLEW_OK) {
				rse::utils::LogError("Could not initialize GLEW");
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			rse::utils::Log("OpenGL: ", (char *)glGetString(GL_VERSION));
			
			return true;
		}

		void Window::setBackground(unsigned int color) const {
			float a = ((color >> 24) & 0x000000ff) / 255.0f;
			float r = ((color >> 16) & 0x000000ff) / 255.0f;
			float g = ((color >> 8) & 0x000000ff) / 255.0f;
			float b = (color & 0x000000ff) / 255.0f;
			glClearColor(r,g,b,a);
		}

		void Window::setWindowIcon(const std::string& filename) const {
			GLFWimage images[1];
			int width, height, bitsperpixels;
			BYTE* pixels = utils::load_image(filename.c_str(), &width, &height, &bitsperpixels);
			for (int i = 0; i < width*height*4; i+=4) {
				unsigned char c = pixels[i + 0];
				pixels[i + 0] = pixels[i + 2];
				pixels[i + 2] = c;
			}
			images[0] = { width, height, pixels };
			
			glfwSetWindowIcon(m_Window, 1, images);
			delete[] pixels;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			//Update Desktop input states
			input::Desktop::update();
			
			//TODO: Handle glErrors where the error occurs
			/*GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
				system("PAUSE");
			}*/

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		void Window::close() const {
			glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			glViewport(0, 0, width, height);
			win->m_Width = width;
			win->m_Height = height;
		}
	}
}