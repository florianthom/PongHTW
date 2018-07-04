#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "iostream"
#include "text2D.h"
#include "texture.hpp"
#include "State.h"
#include "objects.hpp"



#pragma once
class Triangle : public State
{
private:
	GLuint* programmID;
	glm::mat4 ModelTriangle;
	unsigned int VAO1;
	glm::mat4 * View;
	glm::mat4 * Projection;
	GLuint TextureOrange;
	GLuint TextureStone;

	void sendModel(glm::mat4 ModelToSend);
public:
	Triangle(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Triangle();
	void drawTriangleThroughObject(GLuint TextureOrange);
	void drawSzene();


	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void printControlKeysToConsole();
	void enterState();
	void exitState();
	Triangle();
	void lol();

};



