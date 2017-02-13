#version 330 core

layout (location=0) in vec3 cube_pos;
layout (location=1) in vec2 cube_texture;

out vec2 texture_coord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){
	gl_Position = Projection * View * Model * vec4(cube_pos.x, cube_pos.y, cube_pos.z, 1.0f);
	texture_coord = cube_texture;
}