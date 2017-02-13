#include "Entity.hpp"
#include "cmath"

#include "../GameState/GameState.hpp"

glm::vec3 Entity::Up;
extern GameState game;

void Entity::init(){
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Entity::Entity(){
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);
	eye = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = 0.0f;
	pitch = 0.0f;

	model = glm::mat4();
	view = glm::mat4();
	projection = glm::mat4();

	cX = floor(position.x/16);
	cZ = floor(position.z/16);

	LcX = floor(position.x/16);
	LcZ = floor(position.z/16);
}

Entity::Entity(glm::vec3 pos){
	position = pos;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);
	eye = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = 0.0f;
	pitch = 0.0f;

	model = glm::mat4();
	view = glm::mat4();
	projection = glm::mat4();
	cX = floor(position.x/16);
	cZ = floor(position.z/16);

	LcX = floor(position.x/16);
	LcZ = floor(position.z/16);
}

void Entity::update(){
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 eye;

	eye.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	eye.y = sin(glm::radians(pitch));
	eye.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	right.x = cos(glm::radians(yaw));
	right.y = 0;
	right.z = sin(glm::radians(yaw));

	up = glm::cross(right, eye);
	eye = glm::cross(up, right);

	front.x = right.z;
	front.y = right.y;
	front.z = -right.x;

	this->eye = glm::normalize(eye);
	this->up = glm::normalize(up);
	this->Right = glm::normalize(right);
	this->Front = glm::normalize(front);

	view = glm::lookAt(position, position + eye, up);
	projection = glm::perspective(45.0f, (float)800/(float)600, 0.1f, 100.0f);

	cX = position.x/16;
	cZ = position.z/16;

	if(cX != LcX || cZ != LcZ)
		game.update_chunk();

	LcX = cX;
	LcZ = cZ;
}

glm::mat4 Entity::get_model(){
	return model;
}

glm::mat4 Entity::get_view(){
	return view;
}

glm::mat4 Entity::get_projection(){
	return projection;
}

void Entity::s_yaw(double d){
	yaw += d;

	if(yaw > 180.0f)
		yaw -= 360.0f;
	if(yaw < -180.0f)
		yaw += 360.0f;
}

void Entity::s_pitch(double d){
	pitch += d;

	if(pitch < -89.9f)
		pitch = -89.9f;
	if(pitch > 89.9f)
		pitch = 89.9f;
}