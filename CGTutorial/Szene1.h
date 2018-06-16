#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#include "iostream"
#include "State.h"

#pragma once
class Szene1 : public State
{
private:
	GLuint* programmID;
	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;
	glm::mat4 ModelAll;
	Ball* ball1;

	glm::mat4 * View;
	glm::mat4 * Projection;
	glm::vec3 Position;
	double groesse;
	void sendModel(glm::mat4 ModelToSend);
public:
	Szene1(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	Szene1();
	~Szene1();
	virtual void drawSzene();

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void enterState();
	void exitState();
	void lol();
};

