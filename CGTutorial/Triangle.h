#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "iostream"
#pragma once
class Triangle
{
private:
	GLuint* programmID;
	glm::mat4 ModelTriangle;
	unsigned int VAO1;
	glm::mat4 * View;
	glm::mat4 * Projection;

	void sendModel(glm::mat4 ModelToSend);
public:
	Triangle(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Triangle();
	void drawTriangleThroughObject(GLuint TextureOrange);

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);

};



