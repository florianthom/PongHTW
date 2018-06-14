#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "iostream"
#pragma once
class MainMenu
{
private:
	GLuint* programmID;

	glm::mat4 ModelAll;

	glm::mat4 * View;
	glm::mat4 * Projection;
	glm::vec3 Position;

	void sendModel(glm::mat4 ModelToSend);
public:
	MainMenu(GLuint * programID, glm::mat4* v, glm::mat4* p);
	~MainMenu();
	void drawSzene();

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
};