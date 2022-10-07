#include "desktop.h"

namespace rse {
	namespace input {

		unsigned char Desktop::m_Keys[MAX_KEYS];
		unsigned char Desktop::m_KeyState[MAX_KEYS];
		
		unsigned char Desktop::m_MouseButtons;
		unsigned char Desktop::m_MouseButtonState;
		double Desktop::mx, Desktop::my;
		int Desktop::m_ScrollX, Desktop::m_ScrollY;
		bool Desktop::m_CursorVisible;
		GLFWwindow *Desktop::m_Window;

		void Desktop::toggleCursorVisibility() {
			if(m_CursorVisible)
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_CursorVisible = !m_CursorVisible;
		}

		bool Desktop::isKeyPressed(unsigned int keycode) {
			//the key state representing the 'keycode' will be (keycode % 8) bit from LSB of m_Keys[int(keycode / 8)]
			if (int(keycode/8) >= MAX_KEYS) {
				utils::LogError("Keycode not defined");
				return false;
			}

			return (m_Keys[int(keycode / 8)] >> (keycode % 8)) & 1;
		}

		bool Desktop::isKeyReleased(unsigned int keycode) {
			//the key state representing the 'keycode' will be (keycode % 8) bit from LSB of m_Keys[int(keycode / 8)]
			if (int(keycode / 8) >= MAX_KEYS) {
				utils::LogError("Keycode not defined");
				return false;
			}

			return ((m_KeyState[int(keycode / 8)] >> (keycode % 8)) & 1) && !((m_Keys[int(keycode / 8)] >> (keycode % 8)) & 1);
		}

		bool Desktop::isKeyTyped(unsigned int keycode) {
			//the key state representing the 'keycode' will be (keycode % 8) bit from LSB of m_Keys[int(keycode / 8)]
			if (int(keycode / 8) >= MAX_KEYS) {
				utils::LogError("Keycode not defined");
				return false;
			}

			return !((m_KeyState[int(keycode / 8)] >> (keycode % 8)) & 1) && ((m_Keys[int(keycode / 8)] >> (keycode % 8)) & 1);
		}

		bool Desktop::isMouseButtonPressed(unsigned int button) {
			if (int(button / 8) > 1) {
				utils::LogError("Button key not defined");
				return false;
			}

			return (m_MouseButtons >> (button % 8)) & 1;
		}

		bool Desktop::isMouseButtonReleased(unsigned int button) {
			if (int(button / 8) > 1) {
				utils::LogError("Button key not defined");
				return false;
			}
			
			return ((m_MouseButtonState >> (button % 8)) & 1) && !((m_MouseButtons >> (button % 8)) & 1);
		}
		
		bool Desktop::isMouseButtonClicked(unsigned int button) {
			if (int(button/8) > 1) {
				utils::LogError("Button key not defined");
				return false;
			}

			return !((m_MouseButtonState >> (button % 8)) & 1) && ((m_MouseButtons >> (button % 8)) & 1);
		}

		void Desktop::getMousePosition(double &x, double &y) {
			x = mx;
			y = my;
		}

		void Desktop::getMouseScroll(int &x, int &y) {
			x = m_ScrollX;
			y = m_ScrollY;
		}

		void Desktop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			//the key state representing the 'keycode' will be (keycode % 8) bit from LSB of m_Keys[int(keycode / 8)]
			//rightShifted char cyclic right shifts the element and sets the LSB to 0, this will be optimized by compiler in release mode
			unsigned char rightShifted = ((m_Keys[int(key / 8)] >> (key % 8)) | (m_Keys[int(key / 8)] << (CHAR_BIT - (key % 8)))) & 254;
			m_Keys[int(key / 8)] = action != GLFW_RELEASE? ((rightShifted | 1) << (key % 8)) | ((rightShifted | 1) >> (CHAR_BIT - (key % 8))) : (rightShifted << (key % 8)) | (rightShifted >> (CHAR_BIT - (key % 8)));
		}

		void Desktop::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			unsigned char rightShifted = ((m_MouseButtons >> (button % 8)) | (m_MouseButtons << (CHAR_BIT - (button % 8)))) & 254;
			m_MouseButtons = action != GLFW_RELEASE? ((rightShifted | 1) << (button % 8)) | ((rightShifted | 1) >> (CHAR_BIT - (button % 8))) : (rightShifted << (button % 8)) | (rightShifted >> (CHAR_BIT - (button % 8)));
		}

		void Desktop::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			mx = xpos;
			my = ypos;
		}

		void Desktop::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
			m_ScrollX = xoffset == 0 ? 0 : xoffset < 0 ? -1 : 1;
			m_ScrollY = yoffset == 0 ? 0 : yoffset < 0 ? -1 : 1;
		}

		void Desktop::update() {
			memcpy(m_KeyState, m_Keys, MAX_KEYS);
			m_MouseButtonState = m_MouseButtons;
			m_ScrollX = 0;
			m_ScrollY = 0;
		}
	}
}