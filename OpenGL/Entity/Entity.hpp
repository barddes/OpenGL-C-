#include "../Includes.hpp"

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

class Entity{
	friend class Callback;
	friend class GameState;
	friend class Window;
	static glm::vec3 Up;

	glm::mat4 model, view, projection;
	glm::vec3 Front, Right;
	glm::vec3 up, eye;
	glm::vec3 position;
	int cX, cZ;
	int LcX, LcZ;

	double yaw, pitch;


	public:
		static void init();
		Entity();
		Entity(glm::vec3 pos);
		void update();
		glm::mat4 get_model();
		glm::mat4 get_view();
		glm::mat4 get_projection();

		void s_yaw(double d);
		void s_pitch(double d);
};

#endif