#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Positions.hpp"
#include "GlobalTime.hpp"
#pragma once
class Ball
{
private:
	GLuint* programmID;
	const double velocity = 0.6;
	double distance;
	double time;
	const float SCALE = 0.0625f;
	float x;
	float y;
	glm::mat4 Model;
	glm::mat4* View;
	glm::mat4* Projection;
	glm::vec3 position;
	glm::vec3 direction;

	void sendModel();
public:
	Ball(GLuint* programID, glm::mat4* v, glm::mat4* p);
	Ball(GLuint* programID, glm::mat4* v, glm::mat4* p, glm::vec3 newPos);
	~Ball();
	void resetBall();
	void moveBall();
	void changeDirection(glm::vec3 newDirect);
	glm::vec3 getCurrentDirection();
	glm::vec4 getBallPosition();
	glm::vec4 getBallUpLeftPosition();
	glm::vec4 getBallUpRightPosition();
	glm::vec4 getBallDownLeftPosition();
	glm::vec4 getBallDownRightPosition();
	void set_initial_position();
};

