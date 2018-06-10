#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Ball.hpp"
#include "Positions.hpp"
#pragma once

class Collision {
public:
	static bool checkCollision(glm::mat4* border, Ball* ball);
	static void doWallCollision(glm::mat4* border, Ball* ball, glm::vec3 normal);
};