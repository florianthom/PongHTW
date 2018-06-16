#include "State.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#include "iostream"
#include "Szene1.h"
#include "Triangle.h"

#pragma once
class StateContext
{
public:
	StateContext(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~StateContext();
	void set_state(State * new_state);
	State * get_active_state();
	void drawSzene();
	GLuint * get_program_id();
	glm::mat4* get_view();
	glm::mat4* get_projection();
	double get_groesse();
private:
	State * active_state;
	GLuint * programID;
		glm::mat4* v;
		glm::mat4* p;
		double groesse;
};

