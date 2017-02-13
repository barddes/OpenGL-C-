#include "iostream"

#include "../Includes.hpp"

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

class Window{
	friend class Entity;
	
	public:
		static GLuint nWindow;
		static void resizable(GLboolean state);

		Window(const char* name);
		Window(const char* name, GLuint width, GLuint height);
		
		void grab_input();
		void release_input();
		GLboolean should_close();
		void render();
		void swap_buffer();
		void update_size();
		void destroy();
		void set_context();
		void set_callbacks();
		void close();
		void view_port();
		static void draw_cubes_db();
		static int render_cube(int x, int y, int z, int ID);

		GLFWwindow* window;
	private:
		GLint width;
		GLint height;
};

#endif