#include "Ball.hpp"
#include "objects.hpp"


Ball::Ball(GLuint* programID, glm::mat4* v, glm::mat4* p, glm::vec3 direct)
{
	programmID = programID;
	Model = glm::mat4(1.0f);
	View = v;
	Projection = p;
	direction = direct;
	velocity = 5.0;
	lastTime = 0.0;
	time = 0.0;
	Model = glm::scale(Model, glm::vec3(SCALE, SCALE, SCALE));
}

Ball::Ball(GLuint* programID, glm::mat4* v, glm::mat4* p, glm::vec3 newPos, glm::vec3 direct) {
	programmID = programID;
	Model = glm::mat4(1.0f);
	direction = direct;
	velocity = 1.0;
	lastTime = 0.0;
	time = 0.0;
	Model = glm::scale(Model, glm::vec3(SCALE, SCALE, SCALE));
	Model = glm::translate(Model, newPos);
}

Ball::~Ball()
{
	//Model= glm::mat4(1.0f);
	//deleteSphere();
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

glm::vec4 Ball::getBallDownRightPosition() {
	return Position::getRightLowPoint(&Model);
}


