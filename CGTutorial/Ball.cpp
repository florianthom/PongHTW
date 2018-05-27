#include "Ball.hpp"
#include "objects.hpp"


Ball::Ball(GLuint* programID)
{
	programmID = programID;
	Model = glm::mat4(1.0f);
	velocity = 0.4;
	lastTime = 0.0;
	time = 0.0;
}

Ball::Ball(GLuint* programID, glm::vec3 newPos) {
	programmID = programID;
	Model = glm::mat4(1.0f);
	velocity = 0.4f;
	lastTime = 0.0;
	time = 0.0;
	Model = glm::translate(Model, newPos);
}

Ball::~Ball()
{
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

void Ball::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	sendModel();
}

void Ball::moveBall(glm::vec3 move) {
	time = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	distance = velocity * time;
	move.x *= distance;
	move.y *= distance;
	move.z *= distance;
	Model = glm::translate(Model, move);
	sendModel();
	drawSphere(10,10);
}

glm::vec3 Ball::getBallPosition() {
	Position.x = Model[0][3];
	Position.y = Model[1][3];
	Position.z = Model[2][3];
	
	return Position;
}
