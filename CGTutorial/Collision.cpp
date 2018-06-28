#include "Collision.hpp"

bool Collision::checkCollision(glm::mat4* border, Ball* ball) {
	bool collisionX = (Position::getLeftUpperPoint(border).x >= ball->getBallUpLeftPosition().x
		&& Position::getRightLowPoint(border).x <= ball->getBallUpLeftPosition().x) || (Position::getLeftUpperPoint(border).x >= 
			ball->getBallDownRightPosition().x && Position::getRightLowPoint(border).x <= ball->getBallDownRightPosition().x);
	bool collisionY = (Position::getLeftUpperPoint(border).y >= ball->getBallUpLeftPosition().y &&
		Position::getRightLowPoint(border).y <= ball->getBallUpLeftPosition().y) || (Position::getLeftUpperPoint(border).y >= 
			ball->getBallDownRightPosition().y && Position::getRightLowPoint(border).y <= ball->getBallDownRightPosition().y);

	return collisionX && collisionY;
}

bool Collision::checkCollision(glm::mat4* border, Paddle* paddle) {
	bool collisionX = (Position::getLeftUpperPoint(border).x >= paddle->getPaddleUpLeftPosition().x
		&& Position::getRightLowPoint(border).x <= paddle->getPaddleUpLeftPosition().x) || (Position::getLeftUpperPoint(border).x >=
			paddle->getPaddleDownRightPosition().x && Position::getRightLowPoint(border).x <= paddle->getPaddleDownRightPosition().x);
	bool collisionY = (Position::getLeftUpperPoint(border).y >= paddle->getPaddleUpLeftPosition().y &&
		Position::getRightLowPoint(border).y <= paddle->getPaddleUpLeftPosition().y) || (Position::getLeftUpperPoint(border).y >=
			paddle->getPaddleDownRightPosition().y && Position::getRightLowPoint(border).y <= paddle->getPaddleDownRightPosition().y);

	return collisionX && collisionY;
}

bool Collision::checkCollision(Paddle* paddle, Ball* ball, int location) {
	bool collisionX;
	bool collisionY;

	switch (location) {
	case 0:
		collisionX = paddle->getPaddleUpRightPosition().x <= ball->getBallUpLeftPosition().x &&
		(paddle->getPaddleUpRightPosition().x + 0.1f) >= ball->getBallUpLeftPosition().x;
		collisionY = paddle->getPaddleUpRightPosition().y >= ball->getBallUpLeftPosition().y &&
		paddle->getPaddleDownRightPosition().y <= ball->getBallUpLeftPosition().y || paddle->getPaddleUpRightPosition().y >=
		ball->getBallDownLeftPosition().y && paddle->getPaddleDownRightPosition().y <= ball->getBallDownLeftPosition().y;
		break;
	case 1:
		collisionX = paddle->getpaddleDownLeftPosition().x >= ball->getBallUpLeftPosition().x &&
		paddle->getPaddleDownRightPosition().x <= ball->getBallUpLeftPosition().x || paddle->getpaddleDownLeftPosition().x >=
		ball->getBallUpRightPosition().x && paddle->getPaddleDownRightPosition().x <= ball->getBallUpRightPosition().x;
		collisionY = paddle->getpaddleDownLeftPosition().y <= ball->getBallUpLeftPosition().y &&
		(paddle->getPaddleUpLeftPosition().y + 0.1f) >= ball->getBallUpLeftPosition().y;
		break;
	case 2:
		collisionX = paddle->getPaddleUpLeftPosition().x >= ball->getBallUpRightPosition().x &&
		(paddle->getPaddleUpLeftPosition().x - 0.1f) <= ball->getBallUpRightPosition().x;
		collisionY = paddle->getPaddleUpLeftPosition().y >= ball->getBallUpRightPosition().y &&
		paddle->getpaddleDownLeftPosition().y <= ball->getBallUpRightPosition().y || paddle->getPaddleUpLeftPosition().y >=
		ball->getBallDownRightPosition().y && paddle->getpaddleDownLeftPosition().y <= ball->getBallDownRightPosition().y;
		break;
	case 3:
		collisionX = paddle->getPaddleUpLeftPosition().x >= ball->getBallDownLeftPosition().x &&
			paddle->getPaddleUpRightPosition().x <= ball->getBallDownLeftPosition().x || paddle->getPaddleUpRightPosition().x >=
			ball->getBallDownRightPosition().x && paddle->getPaddleUpRightPosition().x <= ball->getBallDownRightPosition().x;
		collisionY = paddle->getPaddleUpLeftPosition().y <= ball->getBallDownLeftPosition().y &&
			(paddle->getPaddleUpLeftPosition().y + 0.1f) >= ball->getBallDownLeftPosition().y;
		break;
	default: printf("Ungueltige Position des Paddles");

	}
	
	return collisionX && collisionY;
}

/*bool Collision::check3DCollision(glm::mat4* level, Ball* ball) {
	bool collision;
	glm::vec4 right_upper = Position::getRightUpperPoint(level);
	glm::vec4 left_down = Position::getLeftLowPoint(level);
	glm::vec4 right_behind_low = Position::getRightBehindLowPoint(level);
	glm::vec4 ball_left_up = ball->getBallUpLeftPosition();
	glm::vec4 ball_right_down = ball->getBallDownRightPosition();
	glm::vec4 ball_right_behind = ball->getBallDownRightBehindPosition();


	// true if ball is inside of the box
	collision = left_down.y < ball_right_down.y && right_upper.y > ball_left_up.y && left_down.x > ball_left_up.x && right_behind_low.x < ball_right_down.x && left_down.z < ball_left_up.z && right_behind_low.z > ball_right_behind.z;
	return !collision;
}*/

// Location -> 0 = left, 1 = up, 2 = right, 3 = down, 4 = front, 5 = back
bool Collision::check3DCollision(glm::vec4 up, glm::vec4 down, Ball* ball, int location) {
	bool collision;
	switch (location) {
	case 0:
		collision = up.z < ball->getBallUpLeftPosition().z && down.z > ball->getBallDownRightPosition().z &&
			up.y > ball->getBallUpLeftPosition().y && down.y < ball->getBallDownRightPosition().y && up.x > ball->getBallUpLeftPosition().x;
		break;
	case 1:
		collision = up.x > ball->getBallUpLeftPosition().x && down.x < ball->getBallDownRightBehindPosition().x &&
			up.z < ball->getBallUpLeftPosition().z && down.z > ball->getBallDownRightBehindPosition().z &&
			up.y > ball->getBallUpLeftPosition().y;
		break;
	case 2:
		collision = up.y > ball->getBallUpLeftPosition().y && down.y < ball->getBallDownRightBehindPosition().y &&
			up.z < ball->getBallUpLeftPosition().z && down.z > ball->getBallDownRightBehindPosition().z &&
			up.x < ball->getBallDownRightBehindPosition().x;
		break;
	case 3:
		collision = up.x > ball->getBallUpLeftPosition().x && down.x < ball->getBallDownRightBehindPosition().x &&
			up.z < ball->getBallUpLeftPosition().z && down.z > ball->getBallDownRightBehindPosition().z &&
			up.y < ball->getBallDownRightBehindPosition().y;
		break;
	case 4:
		collision = up.x > ball->getBallUpLeftPosition().x && down.x < ball->getBallDownRightBehindPosition().x &&
			up.y > ball->getBallUpLeftPosition().y && down.x < ball->getBallDownRightBehindPosition().y &&
			up.z < ball->getBallUpLeftPosition().z;
		break;
	case 5:
		collision = up.x > ball->getBallUpLeftPosition().x && down.x < ball->getBallDownRightBehindPosition().x &&
			up.y > ball->getBallUpLeftPosition().y && down.y < ball->getBallDownRightBehindPosition().y &&
			up.z > ball->getBallDownRightBehindPosition().z;
		break;
	default:
		collision = false;
	}

	return collision;
}


void Collision::doWallBallCollision(glm::mat4* border, Ball* ball, glm::vec3 normal) {
	if (checkCollision(border, ball)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(normal, ballDirection) * normal;
		ball->changeDirection(newDirection);
	}
}

void Collision::doWallCollision(glm::mat4* border, Paddle* paddle, glm::vec3 normal) {
	if (checkCollision(border, paddle)) {
		glm::vec3 paddleDirection = paddle->getCurrentDirection();
		paddleDirection = glm::normalize(paddleDirection);
		glm::vec3 newDirection = paddleDirection - 2.0f * glm::dot(normal, paddleDirection) * normal;
		paddle->changeDirection(newDirection);
	}
}

void Collision::doPaddleCollision(Paddle* paddle, Ball* ball, int location) {
	if (checkCollision(paddle, ball, location)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(paddle->getNormal(), ballDirection) * paddle->getNormal();
		ball->changeDirection(newDirection);
	}
}

void Collision::do3DWallBallCollision(glm::mat4* level, Ball* ball) {
	// Check all walls
	// Check left
	if (check3DCollision(Position::getLeftUpperPoint(level), Position::getLeftBehindLowPoint(level), ball, 0)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(-1.0f,0.0f,0.0f), ballDirection) * glm::vec3(-1.0f, 0.0f, 0.0f);
		ball->changeDirection(newDirection);
	}
	// Check up
	if (check3DCollision(Position::getLeftUpperPoint(level), Position::getRightBehindUpperPoint(level), ball, 1)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(0.0f, -1.0f, 0.0f), ballDirection) * glm::vec3(0.0f, -1.0f, 0.0f);
		ball->changeDirection(newDirection);
	}
	// Check right
	if (check3DCollision(Position::getRightUpperPoint(level), Position::getRightBehindLowPoint(level), ball, 2)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), ballDirection) * glm::vec3(1.0f, 0.0f, 0.0f);
		ball->changeDirection(newDirection);
	}
	// Check down
	if (check3DCollision(Position::getLeftLowPoint(level), Position::getRightBehindLowPoint(level), ball, 3)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), ballDirection) * glm::vec3(0.0f, 1.0f, 0.0f);
		ball->changeDirection(newDirection);
	}
	// Check front
	if (check3DCollision(Position::getLeftUpperPoint(level), Position::getRightLowPoint(level), ball, 4)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), ballDirection) * glm::vec3(0.0f, 0.0f, 1.0f);
		ball->changeDirection(newDirection);
	}
	// Check back
	if (check3DCollision(Position::getLeftBehindUpperPoint(level), Position::getRightBehindLowPoint(level), ball, 5)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		ballDirection = glm::normalize(ballDirection);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(glm::vec3(0.0f, 0.0f, -1.0f), ballDirection) * glm::vec3(0.0f, 0.0f, -1.0f);
		ball->changeDirection(newDirection);
	}
}