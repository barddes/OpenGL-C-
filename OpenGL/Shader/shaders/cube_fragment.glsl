#version 330 core

in vec2 texture_coord;

out vec4 color;

uniform sampler2D Texture;

void main(){
	vec2 coord = texture_coord;
	coord.y = 1-coord.y;
	color = texture(Texture, coord);
	// color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}