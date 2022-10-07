/* ------------INPUT HANDLING CODE------------

//Toggle CursorVisibility
input::Desktop::toggleCursorVisibility();

//Continuous  Key Pressed Detection (return boolean)
input::Desktop::isKeyPressed(GLFW_KEY_A)

//Key Pressed First Time Detection (return boolean)
input::Desktop::isKeyTyped(GLFW_KEY_A)

//Key Released Detection (return boolean)
input::Desktop::isKeyReleased(GLFW_KEY_A)

//Continuous  Mouse Button Clicked Detection (return boolean)
input::Desktop::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)

//Mouse Button Clicked First Time Detection (return boolean)
input::Desktop::isMouseButtonClicked(GLFW_MOUSE_BUTTON_LEFT)

//Mouse Button Released Detection (return boolean)
input::Desktop::isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT)

//To Detect if a key/MouseButton is hold
input::Desktop::isKeyPressed(GLFW_KEY_A) && !input::Desktop::isKeyTyped(GLFW_KEY_A)

NOTE:	is(Key)MouseButtonPressed checks if the (Key)MouseButton is pressed for that current frame,
		is(Key)MouseButtonTyped checks if the (Key)MouseButton is pressed for first time as compared to previous frames
		Thus to check if the (Key)MouseButton is being pressed continously we should use is(Key)MouseButtonPressed && !is(Key)MouseButtonTyped

//Cursor Position Getter
double x,y;
input::Desktop::getMousePosition(x, y); 

//Cursor Scroll State Getter
int x,y;
input::Desktop::getMouseScroll(x, y); */

#pragma once

#include "../graphics/window.h"

namespace rse {
	//Since memory is byte accessable, storing 8 keys sate in one byte is optimal for storage and keeping time to access constant
	#define MAX_KEYS	44  //352 Total keys (352 / 8 bytes)

	namespace input {

		class Desktop {
		private:
			friend class graphics::Window;

			//One unsigned char stores states of 8 keys
			static unsigned char m_Keys[MAX_KEYS];
			static unsigned char m_KeyState[MAX_KEYS];

			//One unsigned char stores states of 8 buttons
			static unsigned char m_MouseButtons;
			static unsigned char m_MouseButtonState;
			static double mx, my;
			static int m_ScrollX, m_ScrollY;
			static bool m_CursorVisible;
			static GLFWwindow *m_Window;

		public:
			static void toggleCursorVisibility();

			static bool isKeyPressed(unsigned int keycode);
			
			static bool isKeyReleased(unsigned int keycode);
			static bool isKeyTyped(unsigned int keycode);

			static bool isMouseButtonPressed(unsigned int button);
			
			static bool isMouseButtonReleased(unsigned int button);
			static bool isMouseButtonClicked(unsigned int button);
			
			static void getMousePosition(double &x, double &y);
			static void getMouseScroll(int &x, int &y);
		private:
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

			static void update();
		};
	}
}