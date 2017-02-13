#include "iostream"

#include "VideoMode.hpp"

int VideoMode::nMonitor;
GLFWmonitor** VideoMode::Monitors;

VideoMode::VideoMode(GLFWmonitor* m){
	const GLFWvidmode* mode = glfwGetVideoMode(m);
	monitor = m;
	width = mode->width;
	height = mode->height;
	refresh_rate = mode->refreshRate;
}

void VideoMode::get_monitors(){
	Monitors = glfwGetMonitors(&nMonitor);
}

void VideoMode::info(){
	info(15);
}

void VideoMode::info(int x){
	std::cout <<  nMonitor << " monitore(s) reconhecido(s)" << std::endl;
	for(int i=0; i<nMonitor; i++){
		const GLFWvidmode* mode = glfwGetVideoMode(Monitors[i]);
		std::cout << "\t";
		if(!i) std::cout << "* "; // Primary Monitor
		if(x&1) std::cout << glfwGetMonitorName(Monitors[i]) << " : ";
		if(x&2) std::cout << mode->width << " x " << mode->height << "  ";
		if(x&4) std::cout << mode->redBits << " | " << mode->greenBits << " | " << mode->blueBits << "  ";
		if(x&8) std::cout << mode->refreshRate << "Hz";
	}
	std::cout << std::endl << std::endl;
}

GLFWmonitor* VideoMode::get_monitor(){
	return monitor;
}

GLuint VideoMode::get_width(){
	return width;
}

GLuint VideoMode::get_height(){
	return height;
}

GLuint VideoMode::get_refresh_rate(){
	return refresh_rate;
}