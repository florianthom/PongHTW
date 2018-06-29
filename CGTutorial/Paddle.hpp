#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Positions.hpp"
#include "objects.hpp"
#include "GlobalTime.hpp"
#pragma once

class Paddle {
protected:
	GLuint* programmID;
	const double VELOCITY = 0.3;
	double time;
	double distance;
	const float SCALEX = 0.0625f;
	const float SCALEY = 0.25f;
	const float SCALEZ = 0.125f;

	// Scalierung der 3D-Szene
	const float SCALEX3D = 1;
	const float SCALEY3D = 1;
	const float SCALEZ3D = 1.0f / 10.0f;

	const float SCALEX3D_CPU = 0.25;
	const float SCALEY3D_CPU = 0.25;
	const float SCALEZ3D_CPU = 1.0f / 10.0f;

	// Integerwert gibt die Position des Paddles an
	// 0 -> links, 1 -> oben, 2 -> rechts, 3 -> unten
	int location;
	glm::vec3 normal;
	glm::vec3 position;
	glm::mat4 Model;
	glm::mat4* View;
	glm::mat4* Projection;

	
	void sendMVP();
public:
	Paddle();
	virtual ~Paddle();
	virtual void movePaddle();
	virtual void movePaddle3D();
	virtual void setInput(glm::vec3 input);
	virtual glm::vec3 getCurrentDirection();
	virtual void changeDirection(glm::vec3 newDirection);
	int getLocation();
	void resetPaddle();
	glm::vec3 getNormal();
	glm::vec4 getPaddleUpLeftPosition();
	glm::vec4 getPaddleUpRightPosition();
	glm::vec4 getpaddleDownLeftPosition();
	glm::vec4 getPaddleDownRightPosition();
	glm::vec4 getPaddleUpLeftBehindPosition();
	glm::vec4 getPaddleDownRightBehindPosition();
};

class CPUPaddle : public Paddle {
private:
	glm::vec3 direction;
public:
	CPUPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, int l);
	CPUPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, int l, bool threeD);
	~CPUPaddle();
	void movePaddle();
	void setInput(glm::vec3 input);
	glm::vec3 getCurrentDirection();
	void changeDirection(glm::vec3 newDirection);
};

class PlayerPaddle : public Paddle {
private:
	glm::vec3 direction;
public:
	PlayerPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, int l);
	PlayerPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, int l, bool threeD);
	~PlayerPaddle();
	void movePaddle();
	void movePaddle3D();

	void setInput(glm::vec3 input);
};