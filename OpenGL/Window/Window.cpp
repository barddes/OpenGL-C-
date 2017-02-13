#include "iostream"
#include "stdlib.h"
#include "cstdlib"
#include "sstream"

#include "Window.hpp"

#include "../Includes.hpp"
#include "../GLFW/GLFW.hpp"
#include "../GameState/GameState.hpp"
#include "../Callback/Callback.hpp"

extern GLfloat vertices[];

extern GLuint indices[];
extern int fff;

extern GameState game;

Window::Window(const char* name){
	window = glfwCreateWindow(game.actV->get_width(), game.actV->get_height(), name, game.actV->get_monitor(), NULL);
	if(!window){
		std::cout << "Error Code 2A: Failed to create GLFW Fullscreen Window" << std::endl;
		GLFW::quit();
		exit(2);
	}
	std::cout << "Created Fullscreen Window \'" << name << "\'" << std::endl;
}

Window::Window(const char* name, GLuint width, GLuint height){
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if(!window){
		std::cout << "Error Code 2B: Failed to create GLFW Windowed Window" << std::endl;
		GLFW::quit();
		exit(2);
	}
	glfwSetWindowPos(window, (game.actV->get_width() - width)/2, (game.actV->get_height() - height)/2);
	std::cout << "Created Windowed Window \'" << name << "\'" << std::endl;
}

void Window::grab_input(){
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::release_input(){
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

GLboolean Window::should_close(){
	return glfwWindowShouldClose(window);
}

void Window::render(){
	glClearColor(0.14f, 0.0f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.actC->update();

	game.Shaders[0]->use();
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, game.Textures[fff]->get_texture());
	// glUniform1i(game.Shaders[0]->get_uniform("Texture"), 0);


	glUniformMatrix4fv(game.Shaders[0]->get_uniform("View"), 1, GL_FALSE, glm::value_ptr(game.actC->get_view()));
	glUniformMatrix4fv(game.Shaders[0]->get_uniform("Projection"), 1, GL_FALSE, glm::value_ptr(game.actC->get_projection()));

	draw_cubes_db();

	swap_buffer();
}

void Window::swap_buffer(){
	glfwSwapBuffers(window);
}

void Window::update_size(){
	GLint nw, nh;
	glfwGetWindowSize(window, &nw, &nh);
	width = nw;
	height = nh;
}

void Window::destroy(){
	std::cout << "Destroying Window" << std::endl;
	glfwDestroyWindow(window);
}

void Window::set_context(){
	glfwMakeContextCurrent(window);
}

void Window::set_callbacks(){
	glfwSetKeyCallback(window, Callback::key_callback);
	glfwSetCursorPosCallback(window, Callback::mouse_callback);
}

void Window::close(){
	glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::view_port(){
	int width, height;
    glfwGetFramebufferSize(game.actW->window, &width, &height);  
    glViewport(0, 0, width, height);
}

void Window::draw_cubes_db(){

	for(int a=0; a<2*game.vision+1; a++)
		for(int b=0; b<2*game.vision+1; b++)
			for(int c=0; c<16; c++)
				for(int d=0; d<256; d++)
					for(int e=0; e<16; e++)
						if(game.chunk[a][b][c][d][e].id!=0){
							int x, y, z, ID;
							ID = game.chunk[a][b][c][d][e].id;
							x = (a-game.vision)*16+c;
							z = (b-game.vision)*16+e;
							y = d;
							render_cube(x, y, z, ID);
						}
}

int Window::render_cube(int x, int y, int z, int ID){
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(x,y,z));
	glUniformMatrix4fv(game.Shaders[0]->get_uniform("Model"), 1, GL_FALSE, glm::value_ptr(model));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, game.Textures[ID-1]->get_texture());
	glUniform1i(game.Shaders[0]->get_uniform("Texture"), 0);

	game.Cube->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	game.Cube->unbind();
	return 0;
}