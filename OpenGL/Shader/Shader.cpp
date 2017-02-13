#include "Shader.hpp"

#include "sstream"
#include "fstream"
#include "string"
#include "stdlib.h"
#include "stdarg.h"

Shader::Shader(){
	active = 0;
}

Shader::Shader (std::string n, std::string sh , ...){
	int num = sh.length();
	active=0;

	name=n;

	va_list names;
	va_start(names,sh);

	for(int i=0; i<num; i++){
		char op = sh[i];
		switch(op){
			case 'V':
				if(!vertexFile.empty()){
					std::cout << "Only one Vertex Shader is allowed!" << std::endl;
					exit(1);
				}
				setVertex(va_arg(names,char*));				
				break;

			case 'G':
				if(!geometryFile.empty()){
					std::cout << "Only one Geometry Shader is allowed!" << std::endl;
					exit(1);
				}
				setGeometry(va_arg(names,char*));
				break;

			case 'F':
				if(!fragmentFile.empty()){
					std::cout << "Only one Fragment Shader is allowed!" << std::endl;
					exit(1);
				}
				setFragment(va_arg(names,char*));
				break;

			default:
				std::cout << "Invalid Shader Type : \'" << op << "\'" << std::endl;
				exit(1);
		}
	}
	va_end(names);
}
void Shader::test(){
	std::cout << "Vertex   : " << vertexFile << std::endl;
	std::cout << "TessCont : " << tessControlFile << std::endl;
	std::cout << "TessEval : " << tessEvaluationFile << std::endl;
	std::cout << "Geometry : " << geometryFile << std::endl;
	std::cout << "Fragment : " << fragmentFile << std::endl;

	std::cout << "Active :" << active << std::endl;
}

void Shader::use(){
	// test();
	glUseProgram(Program);
}

void Shader::setVertex(std::string file){
	vertexFile.clear();
	vertexFile.append(file);
	active |= VERTEX;
}

void Shader::setGeometry(std::string file){
	geometryFile.clear();
	geometryFile.append(file);
	active |= GEOMETRY;
}

void Shader::setFragment(std::string file){
	fragmentFile.clear();
	fragmentFile.append(file);
	active |= FRAGMENT;
}

void Shader::setTessCon(std::string file){
	tessControlFile.clear();
	tessEvaluationFile.append(file);
	active |= TESSCON;
}

void Shader::setTessEval(std::string file){
	tessEvaluationFile.clear();
	tessEvaluationFile.append(file);
	active |= TESSEVAL;
}

void Shader::process(){
	int num = 5 - (vertexFile.empty() + tessControlFile.empty() + tessEvaluationFile.empty() + geometryFile.empty() + fragmentFile.empty());
	GLuint shaders[num];
	Program = glCreateProgram();

	int i=0;
	if(!vertexFile.empty())
		shaders[i++] = loadShader(vertexFile, GL_VERTEX_SHADER);

	if(!tessControlFile.empty())
		shaders[i++] = loadShader(tessControlFile, GL_TESS_CONTROL_SHADER);

	if(!tessEvaluationFile.empty())
		shaders[i++] = loadShader(tessEvaluationFile, GL_TESS_EVALUATION_SHADER);

	if(!geometryFile.empty())
		shaders[i++] = loadShader(geometryFile, GL_GEOMETRY_SHADER);

	if(!fragmentFile.empty())
		shaders[i++] = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	
	for(i=0; i<num; i++)
		glAttachShader(Program, shaders[i]);
	
	
	glLinkProgram(Program);
	checkLink(Program);

	for(i=0; i<num; i++)
		glDeleteShader(shaders[i]);

}

const char* Shader::readFile(std::string name, int* size){
	name.insert(0, "Shader/shaders/");

	std::string code;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);

	try{
		file.open(name.c_str());
		
		if (!file.is_open()){
			std::cout << "FILEEE NOT FOUNDD: " << name << std::endl;
			exit(666);
		}

		std::stringstream filestream;
		filestream << file.rdbuf();
		file.close();
		code = filestream.str();
	}
	catch(std::ifstream::failure e){
		std::cout << "Error: File \'" << name << "\' not succesfully read" << std::endl;
		exit(7);
	}

	(*size) = code.length();

	char* Code = (char*) calloc((*size+1), sizeof(char));
	strcpy(Code, code.c_str());
	Code[*size] = '\0';
	return Code;
}

GLuint Shader::loadShader(std::string file, GLenum type){
	GLuint shader;
	shader = glCreateShader(type);

	int size;
	const char* code = readFile(file, &size);

	glShaderSource(shader, 1, &code, &size);
	glCompileShader(shader);
	checkCompile(shader);

	free((void*) code);

	return shader;
}

void Shader::checkCompile(GLuint shader){
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
		std::cout << "Compilation Error\n";
		char log[512];
		int sz=512;
		glGetShaderInfoLog(shader, 512, &sz, log);

		std::cout << log << std::endl;
		exit(5);
	}
}

void Shader::checkLink(GLuint program){
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success){
		std::cout << "Linkage Error\n";
		char log[512];
		int sz=512;
		glGetProgramInfoLog(program, 512, &sz, log);

		std::cout << log << std::endl;
		exit(6);
	}
}

GLuint Shader::get_program(){
	return Program;
}

GLint Shader::get_uniform(const GLchar * name){
	return glGetUniformLocation(Program, name);
}

void Shader::setName(std::string n){
	name = n;
}

void Shader::getName(std::string& n){
	n = name;
}