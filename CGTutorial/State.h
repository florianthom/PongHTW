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
	State();
	virtual ~State();
	virtual void drawSzene();
	virtual void enterState();
	virtual void exitState();

};

