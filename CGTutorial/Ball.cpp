#include "Ball.hpp"
#include "objects.hpp"


Ball::Ball(GLuint* programID, glm::vec3 direct)
{
	programmID = programID;
	Model = glm::mat4(1.0f);
	direction = direct;
	velocity = 1.0;
	lastTime = 0.0;
	time = 0.0;
}

Ball::Ball(GLuint* programID, glm::vec3 newPos, glm::vec3 direct) {
	programmID = programID;
	Model = glm::mat4(1.0f);
	direction = direct;
	velocity = 1.0;
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

void Ball::moveBall() {
	glm::vec3 tmpDirect = direction;
	time = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	distance = velocity * time;
	tmpDirect.x *= distance;
	tmpDirect.y *= distance;
	tmpDirect.z *= distance;
	Model = glm::translate(Model, tmpDirect);
	sendModel();
	drawSphere(10,10);
}

void Ball::changeDirection(glm::vec3 newDirect) {
	direction = newDirect;
}

glm::vec3 Ball::getBallPosition() {
	position.x = Model[3][0];
	position.y = Model[3][1];
	position.z = Model[3][2];
	
	return position;
}
