#include "../Includes.hpp"

#ifndef _VAO_HPP_
#define _VAO_HPP_

class VAO{
	GLuint id;

	public:
		VAO();

		void add(int pos, GLenum type, int n, GLint data[], int sz);
		void add(int pos, GLenum type, int n, GLfloat data[], int sz);
		void add(int pos, GLenum type, int n, GLboolean data[], int sz);
		void add(int pos, GLenum type, int n, GLuint data[], int sz);
		void add(int pos, GLenum type, int n, GLdouble data[], int sz);
		void ebo(GLuint indices[], int sz);
		void bind();
		static void unbind();
		void enable(int n);
};

#endif