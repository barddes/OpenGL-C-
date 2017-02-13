#include "../Includes.hpp"

#ifndef _VIDEOMODE_HPP_
#define _VIDEOMODE_HPP_

class VideoMode{
	public:
		static int nMonitor;
		static GLFWmonitor** Monitors;
		static void get_monitors() ;
		static void info(int x);
		static void info();

		VideoMode(GLFWmonitor* m);

		GLFWmonitor* get_monitor();
		GLuint get_width();
		GLuint get_height();
		GLuint get_refresh_rate();

	private:
		GLFWmonitor* monitor;
		GLuint width;
		GLuint height;
		GLuint refresh_rate;
};

#endif // _VIDEOMODE_HPP_