#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "State.h"
#include "Ball.hpp"
#include "Collision.hpp"
#pragma once
class Szene2 : public State
{
private:
	GLuint* programmID;
	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;

	glm::mat4 ModelA;
	glm::mat4 ModelB;
	glm::mat4 ModelC;
	glm::mat4 ModelD;
	glm::mat4 ModelE;
	glm::mat4 ModelF;
	glm::mat4 ModelG;
	glm::mat4 ModelH;


	glm::mat4* View;
	glm::mat4* Projection;
	glm::vec3 Position;

	Ball* ball1;
	Paddle* player1_1;
	Paddle* player1_2;
	Paddle* player2_1;
	Paddle* player2_2;
	const glm::vec3 PLAYER1_1POSITION = glm::vec3(26.0f, 0.0f, 0.0f);
	const glm::vec3 PLAYER1_2POSITION = glm::vec3(0.0f, 26.0f, 0.0f);
	const glm::vec3 PLAYER2_1POSITION = glm::vec3(-26.0f, 0.0f, 0.0f);
	const glm::vec3 PLAYER2_2POSITION = glm::vec3(0.0f, -26.0f, 0.0f);
	int player1Points;
	int player2Points;

	double width;
	double height;
	double depth;

	void resetScene();
	void sendModel(glm::mat4 ModelToSend);
public:
	Szene2(GLuint* programID,glm::mat4* v, glm::mat4* p, double groesse);
	~Szene2();
	void drawSzene();
	void doInputPlayer1_1(glm::vec3 input);
	void doInputPlayer1_2(glm::vec3 input);
	void doInputPlayer2_1(glm::vec3 input);
	void doInputPlayer2_2(glm::vec3 input);

	void setMVP(glm::mat4* v, glm::mat4* p);
	void enterState();
	void exitState();
	void lol();
	Szene2();
};

