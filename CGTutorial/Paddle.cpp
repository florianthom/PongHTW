#include "Paddle.hpp"

Paddle::Paddle() {
	time = GlobalTime::getGobalTime();
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

int Paddle::getLocation() {
	return location;
};

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

// l ist location also wo paddle ist: l: 0/2 ist z.B. links und rechts
CPUPaddle::CPUPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position , int l) {
	programmID = id;
	View = v;
	Projection = p;
	this->position = position;
	int start = rand() % 100;
	if (l == 0 || l == 2) {
		if (start < 50) {
			direction = glm::vec3(0.0f, -1.0f, 0.0f);
		}
		else {
			direction = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		Model = glm::scale(Model, glm::vec3(SCALEX, SCALEY, SCALEZ));
	}
	else {
		if (start < 50) {
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
		}
		else {
			direction = glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		Model = glm::scale(Model, glm::vec3(SCALEY, SCALEX, SCALEZ));
	}
	/*if (start < 50) {
		if (l == 0 || l == 2) {
			Model = glm::scale(Model, glm::vec3(SCALEX, SCALEY, SCALEZ));
			direction = glm::vec3(0.0f, -1.0f, 0.0f);
		}
		else {
			Model = glm::scale(Model, glm::vec3(SCALEY, SCALEX, SCALEZ));
			direction = glm::vec3(-1.0f, 0.0f, 0.0f);
		}
	}
	else {
		if (l == 0 || l == 2) {
			direction = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			direction = glm::vec3(1.0f, 0.0f, 0.0f);
		}
	}*/

	switch (l)
	{
	case 0:
		normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		break;
	case 1:
		normal = glm::vec3(0.0f, -1.0f, 0.0f);
		break;
	case 2:
		normal = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 3:
		normal = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	default:
		printf("Ungueltige Position des Paddles");
	}

	Model = glm::translate(Model, position);
	location = l;
}

CPUPaddle::~CPUPaddle() {}

void CPUPaddle::movePaddle(){
	glm::vec3 tmpDirection = direction;
	//deltaTime = glfwGetTime() - lastTime;
	//lastTime = glfwGetTime();
	distance = VELOCITY * time;
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

PlayerPaddle::PlayerPaddle(GLuint* id, glm::mat4* v, glm::mat4* p, glm::vec3 position, int l) {
	programmID = id;
	View = v;
	Projection = p;
	this->position = position;

	if (l == 0 || l == 2) {
		Model = glm::scale(Model, glm::vec3(SCALEX, SCALEY, SCALEZ));
	}
	else {
		Model = glm::scale(Model, glm::vec3(SCALEY, SCALEX, SCALEZ));
	}

	switch (l)
	{
	case 0:
		normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		break;
	case 1:
		normal = glm::vec3(0.0f, -1.0f, 0.0f);
		break;
	case 2:
		normal = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 3:
		normal = glm::vec3(0.0f, 1.0f, 0.0f);
	default:
		printf("Ungueltige Position des Paddles");
	}

	location = l;
	Model = glm::translate(Model, position);
}

PlayerPaddle::~PlayerPaddle() {};

void PlayerPaddle::movePaddle() {
	sendMVP();
	drawCube();
}

void PlayerPaddle::setInput(glm::vec3 input){
	direction = input;
	distance = VELOCITY * time;
	input *= distance;
	Model = glm::translate(Model, input);
	//sendMVP();
	//drawCube();
};