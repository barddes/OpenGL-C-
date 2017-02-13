#include "Texture.hpp"

#include "iostream"
#include "stdlib.h"

Texture::Texture(){
	glGenTextures(1, &id);
}

void Texture::set_texture(const char* name){
	unsigned char* image = SOIL_load_image(name,&width, &height, 0, SOIL_LOAD_RGBA);

	if(!image){
		std::cout << "Error Code 4: Failed to load texture \'" << name << "\'" << std::endl;
		exit(4);
	}

	glBindTexture(GL_TEXTURE_2D, id); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

GLuint Texture::get_texture(){
	return id;
}