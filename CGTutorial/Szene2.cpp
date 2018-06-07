#include "Szene2.h"
#include "objects.hpp"


Szene2::Szene2(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse)
{
	programmID = programID;
	ModelTopBorder = glm::mat4(1.0f);
	ModelButtomBorder = glm::mat4(1.0f);
	ModelLeftBorder = glm::mat4(1.0f);
	ModelRightBorder = glm::mat4(1.0f);

	ModelA = glm::mat4(1.0f);
	ModelB = glm::mat4(1.0f);
	ModelC = glm::mat4(1.0f);
	ModelD = glm::mat4(1.0f);
	ModelE = glm::mat4(1.0f);
	ModelF = glm::mat4(1.0f);
	ModelG = glm::mat4(1.0f);
	ModelH = glm::mat4(1.0f);


	// top and buttom
	ModelTopBorder = glm::scale(ModelTopBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelTopBorder = glm::translate(ModelTopBorder, glm::vec3(0, 80.0 * groesse, 0.0));

	ModelButtomBorder = glm::scale(ModelButtomBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelButtomBorder = glm::translate(ModelButtomBorder, glm::vec3(0, -80.0 * groesse, 0.0));

	// left and right
	ModelRightBorder = glm::rotate(ModelRightBorder, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelRightBorder = glm::scale(ModelRightBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelRightBorder = glm::translate(ModelRightBorder, glm::vec3(0.0, 80 * groesse, 0.0));

	ModelLeftBorder = glm::rotate(ModelLeftBorder, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelLeftBorder = glm::scale(ModelLeftBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelLeftBorder = glm::translate(ModelLeftBorder, glm::vec3(0.0, -80 * groesse, 0.0));

	//little verticals
	ModelC = glm::rotate(ModelC, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelC = glm::scale(ModelC, glm::vec3(0.525 * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelC = glm::translate(ModelC, glm::vec3(0.0, 39 * groesse, 0.0));
	ModelC = glm::translate(ModelC, glm::vec3(2.81 * groesse, 0.0, 0.0));

	ModelF = glm::rotate(ModelF, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelF = glm::scale(ModelF, glm::vec3(0.525 * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelF = glm::translate(ModelF, glm::vec3(0.0, -39 * groesse, 0.0));
	ModelF = glm::translate(ModelF, glm::vec3(2.81 * groesse, 0.0, 0.0));

	ModelB = glm::rotate(ModelB, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelB = glm::scale(ModelB, glm::vec3(0.525 * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelB = glm::translate(ModelB, glm::vec3(0.0, 39 * groesse, 0.0));
	ModelB = glm::translate(ModelB, glm::vec3(-2.81 * groesse, 0.0, 0.0));

	ModelG = glm::rotate(ModelG, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelG = glm::scale(ModelG, glm::vec3(0.525 * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelG = glm::translate(ModelG, glm::vec3(0.0, -39 * groesse, 0.0));
	ModelG = glm::translate(ModelG, glm::vec3(-2.81 * groesse, 0.0, 0.0));

	//little horizontals
	ModelD = glm::scale(ModelD, glm::vec3(0.525f * groesse, 1.0 / 40.0, 1.0 / 40.0));
	/////////////////////////////////////////////
	ModelD = glm::translate(ModelD, glm::vec3(0.0, 39 * groesse, 0.0));
	ModelD = glm::translate(ModelD, glm::vec3(2.81 * groesse, 0.0, 0.0));

	ModelE = glm::scale(ModelE, glm::vec3(0.525f * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelE = glm::translate(ModelE, glm::vec3(0.0, -39 * groesse, 0.0));
	ModelE = glm::translate(ModelE, glm::vec3(2.81 * groesse, 0.0, 0.0));

	ModelA = glm::scale(ModelA, glm::vec3(0.525f * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelA = glm::translate(ModelA, glm::vec3(0.0, 39 * groesse, 0.0));
	ModelA = glm::translate(ModelA, glm::vec3(-2.81 * groesse, 0.0, 0.0));

	ModelH = glm::scale(ModelH, glm::vec3(0.525f * groesse, 1.0 / 40.0, 1.0 / 40.0));

	ModelH = glm::translate(ModelH, glm::vec3(0.0, -39 * groesse, 0.0));
	ModelH = glm::translate(ModelH, glm::vec3(-2.81 * groesse, 0.0, 0.0));



	View = v;
	Projection = p;
}


void Szene2::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	//sendModel();
}

void Szene2::sendModel(glm::mat4 ModelToSend) {
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = *Projection * *View * ModelToSend;
	glm::mat4 ViewTemp = *View;
	glm::mat4 ProjectionTemp = *Projection;
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform, konstant fuer alle Eckpunkte
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "M"), 1, GL_FALSE, &ModelToSend[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "V"), 1, GL_FALSE, &ViewTemp[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(*programmID, "P"), 1, GL_FALSE, &ProjectionTemp[0][0]);
}


void Szene2::drawSzene() {
	
	sendModel(ModelTopBorder);
	drawCube();

	
	sendModel(ModelButtomBorder);
	drawCube();


	sendModel(ModelRightBorder);
	drawCube();

	sendModel(ModelLeftBorder);
	drawCube();

	sendModel(ModelC);
	drawCube();


	sendModel(ModelF);
	drawCube();


	sendModel(ModelB);
	drawCube();

	sendModel(ModelG);
	drawCube();


	sendModel(ModelD);
	drawCube();


	sendModel(ModelE);
	drawCube();


	sendModel(ModelA);
	drawCube();


	sendModel(ModelH);
	drawCube();

}


Szene2::~Szene2()
{
}