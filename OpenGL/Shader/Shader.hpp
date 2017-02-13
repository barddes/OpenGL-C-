#include "../Includes.hpp"

#include "iostream"

#ifndef SHADER_HPP
#define SHADER_HPP

enum{
	VERTEX 		= 0b1,
	GEOMETRY 	= 0b10,
	FRAGMENT 	= 0b100,
	TESSCON 	= 0b1000,
	TESSEVAL 	= 0b10000
};

class Shader{
	public:
		void use();
		void test();
		void process();
		GLuint get_program();
		GLint get_uniform(const GLchar* file);

		Shader();
		Shader(std::string n, std::string sh , ...);
		void setVertex(std::string file);
		void setGeometry(std::string file);
		void setFragment(std::string file);
		void setTessCon(std::string file);
		void setTessEval(std::string file);
		void setName(std::string n);
		void getName(std::string& n);

	private:
		GLuint Program;
		std::string vertexFile;
		std::string tessControlFile;
		std::string tessEvaluationFile;
		std::string geometryFile;
		std::string fragmentFile;

		int active;
		
		std::string name;

		GLuint loadShader(std::string file, GLenum type);
		const char* readFile(std::string file, int* size);
		void checkCompile(GLuint shader);
		void checkLink(GLuint shader);
};

#endif // SHADER