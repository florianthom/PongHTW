#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Positions.hpp"
#include "objects.hpp"
#pragma once

class Paddle {
protected:
	GLuint* programmID;
	const double VELOCITY = 3.0;
	double lastTime;
	double deltaTime;
	double distance;
	const float SCALEX = 0.0625f;
	const float SCALEY = 0.25f;
	const float SCALEZ = 0.125f;
	bool left;
	glm::vec3 normal;
	glm::vec3 position;
	glm::mat4 Model;
	glm::mat4* View;
	glm::mat4* Projection;

	
	virtual void sendMVP();
public:
	Paddle();
	virtual ~Paddle();
	virtual void movePaddle();
	virtual void setInput(glm::vec3 input);
	virtual glm::vec3 getCurrentDirection();
	virtual void changeDirection(glm::vec3 newDirection);
	bool isLeft();
	void resetPaddle();
	glm::vec3 getNormal();
	glm::vec4 getPaddleUpLeftPosition();
	glm::vec4 getPaddleUpRightPosition();
	glm::vec4 getpaddleDownLeftPosition();
	glm::vec4 getPaddleDownRightPosition();
};

class CPUPaddle : public Paddle {
private:
	glm::vec3 direction;
public:
	CPUPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, glm::vec3 n, bool l);
	~CPUPaddle();
	void movePaddle();
	void setInput(glm::vec3 input);
	glm::vec3 getCurrentDirection();
	void changeDirection(glm::vec3 newDirection);
};