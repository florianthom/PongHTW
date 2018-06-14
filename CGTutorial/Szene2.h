#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ball.hpp"
#include "Collision.hpp"
#pragma once
class Szene2
{
private:
	GLuint* programmID;
	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;

	glm::mat4 ModelA;
	glm::mat4 ModelB;
	glm::mat4 ModelC;
	glm::mat4 ModelD;
	glm::mat4 ModelE;
	glm::mat4 ModelF;
	glm::mat4 ModelG;
	glm::mat4 ModelH;


	glm::mat4* View;
	glm::mat4* Projection;
	glm::vec3 Position;

	Ball* ball1;

	void sendModel(glm::mat4 ModelToSend);
public:
	Szene2(GLuint* programID,glm::mat4* v, glm::mat4* p, double groesse);
	~Szene2();
	void drawSzene();

	void setMVP(glm::mat4* v, glm::mat4* p);
};

