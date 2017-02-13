#include "iostream"
#include "vector"
#include "sqlite3.h"

#include "../Includes.hpp"
#include "../VideoMode/VideoMode.hpp"
#include "../Window/Window.hpp"
#include "../Entity/Entity.hpp"
#include "../VAO/VAO.hpp"
#include "../Data/Data.hpp"
#include "../Texture/Texture.hpp"
#include "../Shader/Shader.hpp"
#include "../Data/Data.hpp"

#ifndef _GAMESTATE_HPP_
#define _GAMESTATE_HPP_

struct block{
	char id;
	bool opaque;
	bool solid;
};

class GameState{
	public:
		std::vector<VideoMode*> Videos;
		VideoMode* actV;

		std::vector<Window*> Windows;
		Window* actW;

		Entity* Camera;
		Entity* fCamera;
		Entity* bCamera;
		Entity* actC;

		Texture** Textures;

		VAO* Cube;
		VAO *Cube_top,
			*Cube_left,
			*Cube_right,
			*Cube_bottom,
			*Cube_front,
			*Cube_back;

		Shader** Shaders;

		block***** chunk;

		sqlite3* db;

		static short vision;

		static float deltaTime;

		void video_config();
		void create_window(const char* name);
		void create_window(const char* name, GLuint width, GLuint height);
		void clean();
		void update_win();
		void camera_init();
		void gen_cube_VAO();
		void load_texture();
		void shaders_init();
		void update_time();
		void open_db();
		void close_db();
		void chunk_init();
		void load_chunk(int a, int b, int ca, int cb);
		static int set(void* p, int num, char** val, char** label);
		void update_chunk();
};

#endif