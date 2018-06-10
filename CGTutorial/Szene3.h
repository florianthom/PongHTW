#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "iostream"
#pragma once
class Szene3
{
private:
	GLuint* programmID;
	glm::mat4 InitialBalkenModel;
	glm::mat4 InitialBalkenModel2;
	glm::mat4 EnvironmentCube;

	glm::mat4 ModelTopBorder;
	glm::mat4 ModelButtomBorder;
	glm::mat4 ModelLeftBorder;
	glm::mat4 ModelRightBorder;
	glm::mat4 ModelAll;

	glm::mat4 * View;
	glm::mat4 * Projection;

	void sendModel(glm::mat4 ModelToSend);
public:
	Szene3(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Szene3();
	void drawSzene(GLuint TextureOrigin, GLuint TextureIWantToUse, GLuint Additional);

	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
};

