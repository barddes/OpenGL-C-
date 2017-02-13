#include "../Includes.hpp"

#ifndef _CALLBACK_HPP_
#define _CALLBACK_HPP_

class Callback{
	public:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void do_movement();
		static bool keys[1024];
};

#endif