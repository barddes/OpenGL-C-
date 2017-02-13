#include "VAO.hpp"

VAO::VAO(){
	glGenVertexArrays(1, &id);
}

void VAO::add(int pos, GLenum type, int n, GLint data[], int sz){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sz*n*sizeof(GLint), data, GL_STATIC_DRAW);
	glVertexAttribPointer(pos, n, GL_INT, GL_FALSE, n*sizeof(GLint), NULL);
	glBindBuffer(type, 0);
}

void VAO::add(int pos, GLenum type, int n, GLfloat data[], int sz){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sz*n*sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(pos, n, GL_FLOAT, GL_FALSE, n*sizeof(GLfloat), NULL);
	glBindBuffer(type, 0);
}

void VAO::add(int pos, GLenum type, int n, GLboolean data[], int sz){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sz*n*sizeof(GLboolean), data, GL_STATIC_DRAW);
	glVertexAttribPointer(pos, n, GL_BOOL, GL_FALSE, n*sizeof(GLboolean), NULL);
	glBindBuffer(type, 0);
}

void VAO::add(int pos, GLenum type, int n, GLuint data[], int sz){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sz*n*sizeof(GLuint), data, GL_STATIC_DRAW);
	glVertexAttribPointer(pos, n, GL_UNSIGNED_INT, GL_FALSE, n*sizeof(GLuint), NULL);
	glBindBuffer(type, 0);
}

void VAO::add(int pos, GLenum type, int n, GLdouble data[], int sz){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(type, vbo);
	glBufferData(type, sz*n*sizeof(GLdouble), data, GL_STATIC_DRAW);
	glVertexAttribPointer(pos, n, GL_DOUBLE, GL_FALSE, n*sizeof(GLdouble), NULL);
	glBindBuffer(type, 0);
}

void VAO::ebo(GLuint indices[], int sz){
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sz*sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void VAO::bind(){
	glBindVertexArray(id);
}

void VAO::unbind(){
	glBindVertexArray(0);
}

void VAO::enable(int n){
	glEnableVertexAttribArray(n);
}