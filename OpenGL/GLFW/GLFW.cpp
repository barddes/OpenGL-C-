#include "iostream"
#include "stdlib.h"

#include "GLFW.hpp"
#include "../Includes.hpp"
#include "../GameState/GameState.hpp"

extern GameState game;

void GLFW::init(){
	if(!glfwInit()){
		std::cout << "Error code 1: Failed to initialize GLFW" << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(1);
	}
}

void GLFW::quit(){
	glfwTerminate();
	std::cout << "GLFW Terminated" << std::endl;
}

void GLFW::config(){
	std::cout << "\tOpenGL Version: " << BOLDGREEN << "3.3" << RESET << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	std::cout << "\tDeprecated functions: " << OFF << std::endl;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "\tAuto-Iconify: " << OFF << std::endl;
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

	std::cout << "\tResizable Windows: " << OFF << std::endl;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	std::cout << "\tVSync: " << BOLDGREEN << "ON" << RESET  << std::endl;
	glfwWindowHint(GLFW_REFRESH_RATE, game.actV->get_refresh_rate());

	// std::cout << "\tAnti-Aliasing: " << BOLDGREEN << "16x" << RESET << std::endl;
	// glfwWindowHint(GLFW_SAMPLES, 16);
	// glEnable(GL_MULTISAMPLE);
}