#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#include "iostream"
//#include "StateContext.h"
#pragma once
class State
{
public:

	virtual void drawSzene() = 0;
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void lol() = 0;

};

