#include "Paddle.hpp"

Paddle::Paddle() {
	lastTime = 0.0;
	Model = glm::mat4(1.0f);
};

Paddle::~Paddle(){}

void Paddle::sendMVP(){
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = *Projection * *View * Model;
	glm::mat4 ViewTemp = *View;
	glm::mat4 ProjectionTemp = *Projection;
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform, konstant fuer alle Eckpunkte
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "V"), 1, GL_FALSE, &ViewTemp[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "P"), 1, GL_FALSE, &ProjectionTemp[0][0]);
}

void Paddle::movePaddle(){}

void Paddle::setInput(glm::vec3 input){}

glm::vec3 Paddle::getCurrentDirection() { return glm::vec3(); };

void Paddle::changeDirection(glm::vec3 newDirection) {};

bool Paddle::isLeft() {
	return left;
}

void Paddle::resetPaddle() {
	Model[3][0] = 0.0f;
	Model[3][1] = 0.0f;
	Model[3][2] = 0.0f;
	Model = glm::translate(Model, position);
}

glm::vec3 Paddle::getNormal() {
	return normal;
}

glm::vec4 Paddle::getPaddleUpLeftPosition() {
	return Position::getLeftUpperPoint(&Model);
}

glm::vec4 Paddle::getPaddleUpRightPosition() {
	return Position::getRightUpperPoint(&Model);
}

glm::vec4 Paddle::getpaddleDownLeftPosition() {
	return Position::getLeftBehindLowPoint(&Model);
}

glm::vec4 Paddle::getPaddleDownRightPosition() {
	return Position::getRightLowPoint(&Model);
}

CPUPaddle::CPUPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position ,glm::vec3 n, bool l) {
	programmID = id;
	View = v;
	Projection = p;
	Model = glm::scale(Model, glm::vec3(SCALEX, SCALEY, SCALEZ));
	Model = glm::translate(Model, position);
	this->position = position;
	int start = rand() % 100;
	if (start < 50) {
		direction = glm::vec3(0.0f, -1.0f, 0.0f);
	}
	else {
		direction = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	normal = n;
	left = l;
}

CPUPaddle::~CPUPaddle() {}

void CPUPaddle::movePaddle(){
	glm::vec3 tmpDirection = direction;
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	distance = VELOCITY * deltaTime;
	tmpDirection *= distance;
	Model = glm::translate(Model, tmpDirection);
	sendMVP();
	drawCube();
}

void CPUPaddle::setInput(glm::vec3 input){}

glm::vec3 CPUPaddle::getCurrentDirection() {
	return direction;
}

void CPUPaddle::changeDirection(glm::vec3 newDirection) {
	direction = newDirection;
}