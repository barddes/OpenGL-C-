#include "iostream"
#include "stdlib.h"
#include "stdio.h"


#include "GLFW/GLFW.hpp"
#include "VideoMode/VideoMode.hpp"
#include "GameState/GameState.hpp"
#include "Window/Window.hpp"
#include "GLEW/GLEW.hpp"
#include "Entity/Entity.hpp"
#include "Callback/Callback.hpp"

#include <unistd.h>

GameState game;
int fff;

int main(){
	fff=0;
	system("clear");
	std::cout<< "=-=-=-=-= Starting =-=-=-=-=" << std::endl<< std::endl;

	std::cout << "Iniciando GLFW" << std::endl;
	GLFW::init();
	std::cout << std::endl;

	game.video_config();

	std::cout << "Configurando GLFW" << std::endl;
	GLFW::config();
	std::cout << std::endl;

	game.create_window("OpenGL", 800, 600);
	game.actW->grab_input();

	GLEW::init();
	GLEW::config();
	std::cout << std::endl;

	game.actW->view_port();

	Entity::init();
	game.camera_init();

	game.gen_cube_VAO();
	game.load_texture();

	game.shaders_init();
	

	game.actW->set_callbacks();

	game.open_db();

	game.vision = 1;

	// std::cout << "Prontos? :D" << std::endl;
	// scanf("%*c");
	glfwSetTime	(0.0f);
	game.chunk_init();
	// game.load_chunk(1,1,1,1);
	// scanf("%*c");

	while(!game.Windows.empty()){
		glfwPollEvents();
		game.update_time();
		Callback::do_movement();
		game.actW->render();
		game.update_win(); // Check for windows to close
	}
	
	game.close_db();
	GLFW::quit();
	std::cout<< "=-=-=-=-= Ending =-=-=-=-=" << std::endl << std::endl;
	return 0;
}
