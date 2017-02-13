#include "GLEW.hpp"

#include "../Includes.hpp"
#include "iostream"
#include "stdlib.h"

void GLEW::init(){
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		std::cout << "Error Code 3: Failed to initialize GLEW" << std::endl;
		exit(3);
	}
}

void GLEW::config(){
	std::cout << "Configurando GLEW" << std::endl;
	std::cout << "\tRender back faces: " << OFF << std::endl;
	glEnable(GL_CULL_FACE);
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	std::cout << "\tDepth Test: " << ON << std::endl;
	glEnable(GL_DEPTH_TEST);

	std::cout << "\tBlend colors: " << ON << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// float borderColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}