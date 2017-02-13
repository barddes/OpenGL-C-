#include "../Includes.hpp"

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

class Texture{
	int width, height;
	GLuint id;

	public:
		Texture();
		void set_texture(const char* name);
		GLuint get_texture();
};

#endif