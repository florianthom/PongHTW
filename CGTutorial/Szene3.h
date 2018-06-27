#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "iostream"
#include "State.h"
#include "texture.hpp"
#include "Ball.hpp"

#pragma once
class Szene3 : public State
{
private:
	GLuint* programmID;
	glm::mat4 InitialBalkenModel;
	glm::mat4 InitialBalkenModel2;
	glm::mat4 EnvironmentCube;

	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;
	glm::mat4 ModelAll;

	Ball* ball1;

	int player1Points;
	int player2Points;
	char text[256];
	Paddle* player1;
	Paddle* player2;

	glm::mat4 * View;
	glm::mat4 * Projection;
	GLuint TextureMandrill;
	GLuint TextureStripes;
	GLuint TextureGreen;

	void sendModel(glm::mat4 ModelToSend);
public:
	Szene3(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Szene3();
	void drawSzene();

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void enterState();
	void exitState();
		void lol();
	Szene3();

	void doPlayerInput(glm::vec3 input, int l, bool threeD);
};

