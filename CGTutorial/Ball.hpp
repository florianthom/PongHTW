#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Positions.hpp"
#pragma once
class Ball
{
private:
	GLuint* programmID;
	double velocity;
	double distance;
	double lastTime;
	double time;
	const float SCALE = 0.125f;
	glm::mat4 Model;
	glm::mat4* View;
	glm::mat4* Projection;
	glm::vec3 position;
	glm::vec3 direction;

	void sendModel();
public:
	Ball(GLuint* programID, glm::mat4* v, glm::mat4* p, glm::vec3 direct);
	Ball(GLuint* programID, glm::mat4* v, glm::mat4* p, glm::vec3 newPos, glm::vec3 direct);
	~Ball();
	void moveBall();
	void changeDirection(glm::vec3 newDirect);
	glm::vec3 getCurrentDirection();
	glm::vec4 getBallPosition();
	glm::vec4 getBallUpLeftPosition();
	glm::vec4 getBallDownRightPosition();
};

