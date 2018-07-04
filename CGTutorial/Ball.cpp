#include "Ball.hpp"

Ball::Ball(GLuint* programID, glm::mat4* v, glm::mat4* p)
{
	x = (rand() % 80);
	x /= 100;
	x += 0.4f;
	y = 1 - x;
	programmID = programID;
	Model = glm::mat4(1.0f);
	View = v;
	Projection = p;
	direction = glm::vec3(x, y, 0.0f);
	time = GlobalTime::getGobalTime();
	Model = glm::scale(Model, glm::vec3(SCALE, SCALE, SCALE));
	velocity = 1.3;
}

Ball::Ball(GLuint* programID, glm::mat4* v, glm::mat4* p,bool threeD)
{
	x = (rand() % 101);
	x /= 100;
	x += 0.2f;
	y = 1 - x;
	z = (rand() % 15);
	programmID = programID;
	Model = glm::mat4(1.0f);
	View = v;
	Projection = p;
	direction = glm::vec3(x, y, z);
	time = GlobalTime::getGobalTime();
	Model = glm::scale(Model, glm::vec3(1.2 * SCALE, 1.2 * SCALE, 1.2 * SCALE));
	velocity = 3.0;
}

Ball::~Ball()
{
}

void Ball::set_initial_position() {
	Model = glm::mat4(1.0f);
	Model = glm::scale(Model, glm::vec3(SCALE, SCALE, SCALE));
	sendModel();

}



void Ball::sendModel() {
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

void Ball::resetBall() {
	Model[3][0] = 0.0f;
	Model[3][1] = 0.0f;
	Model[3][2] = 0.0f;
	x = (rand() % 100) + 1;
	x /= 100;
	x += 0.2f;
	y = 1 - x;
	direction = glm::vec3(x, y, 0.0f);
}

void Ball::resetBall3D() {
	Model[3][0] = 0.0f;
	Model[3][1] = 0.0f;
	Model[3][2] = 0.0f;
	z = rand() % 101;
	z /= 100;
	z += 0.5;
	x = 1 - z;
	y = (1 - z) - 0.2;
	direction = glm::vec3(x, y, -1*z);
}

void Ball::moveBall() {
	glm::vec3 tmpDirect = direction;
	distance = velocity * time;
	tmpDirect *= distance;
	tmpDirect /= 10.0f;
	Model = glm::translate(Model, tmpDirect);
	sendModel();
	drawSphere(10,10);
}

glm::vec3 Ball::getCurrentDirection() {
	return direction;
}

void Ball::changeDirection(glm::vec3 newDirect) {
	direction = newDirect;
}

glm::vec4 Ball::getBallPosition() {
	return Position::getCurrentOriginPosition(&Model);
}

glm::vec4 Ball::getBallUpLeftPosition() {
	return Position::getLeftUpperPoint(&Model);
}

glm::vec4 Ball::getBallUpRightPosition() {
	return Position::getRightUpperPoint(&Model);
}

glm::vec4 Ball::getBallDownLeftPosition() {
	return Position::getLeftLowPoint(&Model);
}

glm::vec4 Ball::getBallDownRightPosition() {
	return Position::getRightLowPoint(&Model);
}

glm::vec4 Ball::getBallDownRightBehindPosition() {
	return Position::getRightBehindLowPoint(&Model);
}
