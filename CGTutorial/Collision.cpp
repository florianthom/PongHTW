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

void Collision::doWallCollision(glm::mat4* border, Ball* ball, glm::vec3 normal) {
	if (checkCollision(border, ball)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		//printf("Before: X: %.10f, Y: %.10f, Z: %.10f\n", ballDirection.x, ballDirection.y, ballDirection.z);
		ballDirection = glm::normalize(ballDirection);
		//printf("After: X: %.10f, Y: %.10f, Z: %.10f\n", ballDirection.x, ballDirection.y, ballDirection.z);
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(normal, ballDirection) * normal;
		ball->changeDirection(newDirection);
	}
}

void Collision::doWallCollision(glm::mat4* border, Paddle* paddle, glm::vec3 normal) {
	if (checkCollision(border, paddle)) {
		glm::vec3 paddleDirection = paddle->getCurrentDirection();
		glm::vec3 newDirection = paddleDirection - 2.0f * glm::dot(normal, paddleDirection) * normal;
		paddle->changeDirection(newDirection);
	}
}

void Collision::doPaddleCollision(Paddle* paddle, Ball* ball, int location) {
	if (checkCollision(paddle, ball, location)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(paddle->getNormal(), ballDirection) * paddle->getNormal();
		ball->changeDirection(newDirection);
	}
}