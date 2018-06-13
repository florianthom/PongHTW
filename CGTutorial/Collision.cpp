#include "Collision.hpp"

bool Collision::checkCollision(glm::mat4* border, Ball* ball) {
	bool collisionX = (Position::getLeftUpperPoint(border).x >= ball->getBallUpLeftPosition().x
		&& Position::getRightLowPoint(border).x <= ball->getBallUpLeftPosition().x) || (Position::getLeftUpperPoint(border).x >= 
			ball->getBallDownRightPosition().x && Position::getRightLowPoint(border).x <= ball->getBallDownRightPosition().x);
	bool collisionY = (Position::getLeftUpperPoint(border).y >= ball->getBallUpLeftPosition().y &&
		Position::getRightLowPoint(border).y <= ball->getBallUpLeftPosition().y) || (Position::getLeftUpperPoint(border).y >= 
			ball->getBallDownRightPosition().y && Position::getRightLowPoint(border).y <= ball->getBallDownRightPosition().y);
	
	printf("Kollision auf X-Achse: %d\n", collisionX);
	printf("Kollision auf Y-Achse: %d\n\n", collisionY);

	return collisionX && collisionY;
}

void Collision::doWallCollision(glm::mat4* border, Ball* ball, glm::vec3 normal) {
	if (checkCollision(border, ball)) {
		glm::vec3 ballDirection = ball->getCurrentDirection();
		glm::vec3 newDirection = ballDirection - 2.0f * glm::dot(normal, ballDirection) * normal;

		/*double winkel = (ballDirection.x * normal.x + ballDirection.y * normal.y + ballDirection.z * normal.z) /
			((sqrt(pow(ballDirection.x, 2) + pow(ballDirection.y, 2) + pow(ballDirection.z, 2))) * (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2))));
		winkel = acos(winkel) * 180 / 3.14159265;
		winkel = 180 - winkel;
		
		newDirection.x = normal.x * cos(winkel) - normal.y * sin(winkel);
		newDirection.y = normal.x * cos(winkel) + normal.y * sin(winkel);
		printf("Winkel: %.10f\n", winkel);
		printf("NewDirection x: %.10f y: %.10f\n", newDirection.x, newDirection.y);*/
		//ball->changeDirection(glm::vec3(0.0f, 0.0f, 0.0f));
		printf("newX: %.10f, newY: %.10f, newZ: %.10f", newDirection.x, newDirection.y, newDirection.z);
		ball->changeDirection(newDirection);
	}
}