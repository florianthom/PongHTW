#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Ball.hpp"
#include "Positions.hpp"
#include "Paddle.hpp"
#pragma once

class Collision {
public:
	static bool checkCollision(glm::mat4* border, Ball* ball);
	static bool checkCollision(glm::mat4* border, Paddle* paddle);
	static bool checkCollision(Paddle* paddle, Ball* ball, int location);

	//static bool check3DCollision(glm::mat4* level, Ball* ball);
	static bool check3DCollision(glm::vec4 up, glm::vec4 down, Ball* ball, int location);

	static void doWallBallCollision(glm::mat4* border, Ball* ball, glm::vec3 normal);
	static void doWallCollision(glm::mat4* border, Paddle* paddle, glm::vec3 normal);
	static void doPaddleCollision(Paddle* paddle, Ball* ball, int location);

	static void do3DWallBallCollision(glm::mat4* level, Ball* ball);
};