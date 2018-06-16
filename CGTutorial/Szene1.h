#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#include "iostream"
#include "Paddle.hpp"
#include"text2D.h"
#pragma once
class Szene1
{
private:
	GLuint* programmID;
	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;
	glm::mat4 ModelAll;
	Ball* ball1;
	Paddle* player1;
	Paddle* player2;
	const glm::vec3 PLAYER1POSITION = glm::vec3(26.0f, 0.0f, 0.0f);
	const glm::vec3 PLAYER2POSITION = glm::vec3(-26.0f, 0.0f, 0.0f);
	int player1Points;
	int player2Points;
	char text[256];

	glm::mat4 * View;
	glm::mat4 * Projection;
	glm::vec3 Position;

	void sendModel(glm::mat4 ModelToSend);
	void resetScene();
public:
	Szene1(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Szene1();
	void drawSzene();

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void doInputPlayer1(glm::vec3 input);
	void doInputPlayer2(glm::vec3 input);
};

