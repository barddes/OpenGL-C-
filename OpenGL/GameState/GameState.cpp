#include "GameState.hpp"
#include "stdlib.h"
#include "cmath"
#include "sstream"

extern GameState game;

short GameState::vision;

GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
};

GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3,  // First Triangle
	1, 2, 3   // Second Triangle
};

void GameState::video_config(){
	std::cout << "Recolhendo informacoes sobre video" << std::endl;
	VideoMode::get_monitors();
	VideoMode::info();

	for(int i=0; i<VideoMode::nMonitor; i++){
		VideoMode* v = new VideoMode(VideoMode::Monitors[i]);
		Videos.push_back(v);
	}

	actV = Videos.front();
}

void GameState::create_window(const char* name){
	actW = new Window(name);
	Windows.push_back(actW);
	actW->set_context();
	actW->set_callbacks();
}

void GameState::create_window(const char* name, GLuint width, GLuint height){
	actW = new Window(name, width, height);
	Windows.push_back(actW);
	actW->set_context();
	actW->set_callbacks();
}

void GameState::clean(){
	std::vector<VideoMode*>::iterator i = Videos.begin();

	while(i != Videos.end()){
		delete (*i);
		i++;
	}

	Videos.clear();
	actV = NULL;

	std::vector<Window*>::iterator j = Windows.begin();

	while(j != Windows.end()){
		(*j)->destroy();
		delete (*j);
		j++;
	}

	Windows.clear();
	actW = NULL;
}

void GameState::update_win(){
	std::vector<Window*>::iterator i = Windows.begin();

	while(i != Windows.end()){
		if((*i)->should_close()){
			(*i)->destroy();
			delete (*i);
			i = Windows.erase(i);
			continue;
		}
		i++;
	}
}

void GameState::camera_init(){
	Camera = new Entity();
	fCamera = new Entity();
	bCamera = new Entity();

	actC = Camera;
}

void GameState::gen_cube_VAO(){
	Cube = new VAO();
	Cube->bind();{
		Cube->add(0, GL_ARRAY_BUFFER, 3, cube_pos, 36);
		Cube->add(1, GL_ARRAY_BUFFER, 2, cube_texture, 36);
		Cube->enable(0);
		Cube->enable(1);
	} Cube->unbind();

	Cube_top = new VAO();
	Cube_top->bind();{
		Cube_top->add(0, GL_ARRAY_BUFFER, 3, c_t, 6);
		Cube_top->add(1, GL_ARRAY_BUFFER, 2, ct_t, 6);
		Cube_top->enable(0);
		Cube_top->enable(1);
	} Cube_top->unbind();

	Cube_bottom = new VAO();
	Cube_bottom->bind();{
		Cube_bottom->add(0, GL_ARRAY_BUFFER, 3, c_bt, 6);
		Cube_bottom->add(1, GL_ARRAY_BUFFER, 2, ct_bt, 6);
		Cube_bottom->enable(0);
		Cube_bottom->enable(1);
	} Cube_bottom->unbind();

	Cube_left = new VAO();
	Cube_left->bind();{
		Cube_left->add(0, GL_ARRAY_BUFFER, 3, c_l, 6);
		Cube_left->add(1, GL_ARRAY_BUFFER, 2, ct_l, 6);
		Cube_left->enable(0);
		Cube_left->enable(1);
	} Cube_left->unbind();

	Cube_right = new VAO();
	Cube_right->bind();{
		Cube_right->add(0, GL_ARRAY_BUFFER, 3, c_r, 6);
		Cube_right->add(1, GL_ARRAY_BUFFER, 2, ct_r, 6);
		Cube_right->enable(0);
		Cube_right->enable(1);
	} Cube_right->unbind();

	Cube_front = new VAO();
	Cube_front->bind();{
		Cube_front->add(0, GL_ARRAY_BUFFER, 3, c_f, 6);
		Cube_front->add(1, GL_ARRAY_BUFFER, 2, ct_f, 6);
		Cube_front->enable(0);
		Cube_front->enable(1);
	} Cube_front->unbind();

	Cube_back = new VAO();
	Cube_back->bind();{
		Cube_back->add(0, GL_ARRAY_BUFFER, 3, c_bc, 6);
		Cube_back->add(1, GL_ARRAY_BUFFER, 2, ct_bc, 6);
		Cube_back->enable(0);
		Cube_back->enable(1);
	} Cube_back->unbind();

}

void GameState::load_texture(){
	Textures = (Texture**) calloc(nTextures, sizeof(*Textures));
	for(int i=0; i<nTextures; i++){
		Textures[i] = new Texture();
		std::string name = "Texture/textures/" + lTextures[i];

		Textures[i] ->set_texture(name.c_str());
	}
}

void GameState::shaders_init(){
	Shaders = (Shader**) calloc(nShaders,sizeof(Shader*));

	for(int i=0; i<nShaders; i++){
		Shaders[i] = new Shader();

		Shaders[i]->setName(lShaders[0 + 3*i]);
		Shaders[i]->setVertex(lShaders[1 + 3*i]);
		Shaders[i]->setFragment(lShaders[2 + 3*i]);

		Shaders[i]->process();
	}
}

void GameState::update_time(){
	static float last = 0;
	float cf = glfwGetTime();
	deltaTime = cf - last;
	last = cf;
}

void GameState::open_db(){
	if(sqlite3_open("database.db", &db) != SQLITE_OK){
		std::cout << "Error: Unable to open or create database" << std::endl;
		exit(-1);
	}

	int status;

	status = sqlite3_exec(
		db,                                  /* An open database */
		"CREATE TABLE IF NOT EXISTS World( \
				`Chunk X` INTEGER NOT NULL, \
				`Chunk Y` INTEGER NOT NULL, \
				`x` INTEGER NOT NULL, \
				`y` INTEGER NOT NULL, \
				`z` INTEGER NOT NULL, \
				`ID` INTEGER NOT NULL, \
				`State` INTEGER, \
				PRIMARY KEY(`x`, `y`, `z`) \
		)",     /* SQL to be evaluated */
		NULL,  								 /* Callback function */
		NULL,                                /* 1st argument to callback */
		NULL                              	 /* Error msg written here */
	);

	if(status != SQLITE_OK){
		std::cout << "Algo de errado nao esta certo" << std::endl;
		exit(21);
	}
}

void GameState::close_db(){
	sqlite3_close(db);
}

void GameState::chunk_init(){
	std::cout << "COMEÇO Tempo: " << glfwGetTime() << std::endl;
	int cx=vision*2+1,
		cy=vision*2+1;
	chunk = (block*****) malloc(cx*sizeof(block****));

	for(int a=0; a<cx; a++){
		chunk[a] = (block****) malloc(cy*sizeof(block***));
		for(int b=0; b<cy; b++){
			chunk[a][b] = (block***) malloc(16*sizeof(block**));
			for(int c=0; c<16; c++){
				chunk[a][b][c] = (block**) malloc(256*sizeof(block*));
				for(int d=0; d<256; d++){
					chunk[a][b][c][d] = (block*) calloc(16,sizeof(block));
				}
			}
		}
	}

	for(int i=0; i<2*vision+1; i++){
		for(int j=0; j<2*vision+1; j++){
			// std::cout << "X " << actC->cX-vision+i << ", Z " << actC->cZ-vision+j << "\t" << "X " << i << ", Z " << j << std::endl;
			load_chunk(actC->cX-vision+i, actC->cZ-vision+j, i, j);
		}
	}

	std::cout << "Termino Tempo: " << glfwGetTime() << std::endl;
}

int GameState::set(void* p, int num, char** val, char** label){
	int* pi = (int*) p;

	block*** c = game.chunk[pi[0]][pi[1]];
	int x = atoi(val[0])%16,
		y = atoi(val[1]),
		z = atoi(val[2])%16;

	if(x<0) x+=16;
	if(z<0) z+=16;

	// std::cout << x << " " << y << " " << z << std::endl;

	c[x][y][z].id = atoi(val[3]);
	c[x][y][z].opaque = false;
	return 0;
}

void GameState::load_chunk(int a, int b, int ca, int cb){
	std::stringstream ss;
	ss << "SELECT `x`, `y`, `z`, `ID` FROM World WHERE `Chunk X`="<<a<<" AND `Chunk Y`="<<b<<" ORDER BY `x` ASC";
	std::string str = ss.str();

	int uai[2] ={ca,cb};
	int status = sqlite3_exec(
					db,
					str.c_str(),
					GameState::set,
					uai,
					NULL
	);

	if(status != SQLITE_OK){
		std::cout << "DEU RUIM" << std::endl;
		exit(92);
	}
}

void GameState::update_chunk(){
	short delX, delZ;
	delX = actC->cX - actC->LcX;
	delZ = actC->cZ - actC->LcZ;

	if(delX==1){
		for(int i=0; i<2*vision; i++){
			for(int j=0; j<2*vision+1; j++){
				chunk[i][j] = chunk[i+1][j];
			}
		}
		for(int i=0; i<2*vision+1; i++){
			load_chunk(actC->cX+vision, actC->LcZ-vision+i, 2*vision, i);
		}
	}

	if(delX==-1){
		for(int i=1; i<2*vision+1; i++){
			for(int j=0; j<2*vision+1; j++){
				chunk[i][j] = chunk[i-1][j];
			}
		}
		for(int i=0; i<2*vision+1; i++){
			load_chunk(actC->cX-vision, actC->LcZ-vision+i, 0, i);
		}
	}

	if(delZ==1){
		for(int i=0; i<2*vision+1; i++){
			for(int j=0; j<2*vision; j++){
				chunk[i][j] = chunk[i][j+1];
			}
		}
		for(int i=0; i<2*vision+1; i++){
			load_chunk(actC->cX-vision+i, actC->cZ+vision, i, 2*vision);
		}
	}

	if(delZ==-1){
		for(int i=1; i<2*vision+1; i++){
			for(int j=0; j<2*vision+1; j++){
				chunk[i][j] = chunk[i-1][j];
			}
		}
		for(int i=0; i<2*vision+1; i++){
			load_chunk(actC->cX-vision+i, actC->cZ-vision, i, 0);
		}
	}
}