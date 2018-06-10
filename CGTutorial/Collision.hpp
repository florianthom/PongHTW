#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ball.hpp"
#include "Positions.hpp"
#pragma once

class Collision {
public:
	static bool checkCollision(glm::mat4* border, Ball* ball);
};