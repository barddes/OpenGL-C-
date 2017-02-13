#include "Callback.hpp"

#include "../GameState/GameState.hpp"

extern GameState game;
bool Callback::keys[1024];
float GameState::deltaTime;
extern int fff;

void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		game.actW->close();
	}

	if(key == GLFW_KEY_F && action == GLFW_PRESS)
		fff=(fff+1)%5;

	if(action == GLFW_PRESS){
		keys[key] = true;
	}
	else if(action == GLFW_RELEASE)
		keys[key] = false;
}

void Callback::mouse_callback(GLFWwindow* window, double xpos, double ypos){
	static double lastX;
	static double lastY;
	static bool first = true;

	if(first){
		first = false;
		lastX = xpos;
		lastY = ypos;
		return;
	}

	float sensitivity = 0.25f;

	float delX = (xpos-lastX)*sensitivity;
	float delY = (lastY-ypos)*sensitivity;

	lastX = xpos;
	lastY = ypos;

	game.actC->s_yaw(delX);
	game.actC->s_pitch(delY);
}

void Callback::do_movement(){
	float speed = 8.0f * game.deltaTime;

	Entity* act = game.actC;

	if(keys[GLFW_KEY_LEFT_ALT])
		speed *= 0.1f;

	if(keys[GLFW_KEY_S])
		act->position -= act->Front * speed;
	if(keys[GLFW_KEY_W])
		act->position += act->Front * speed;

	if(keys[GLFW_KEY_A])
		act->position -= act->Right * speed;
	if(keys[GLFW_KEY_D])
		act->position += act->Right * speed;

	if(keys[GLFW_KEY_SPACE])
		act->position += act->Up * speed;
	if(keys[GLFW_KEY_LEFT_SHIFT])
		act->position -= act->Up * speed;
}