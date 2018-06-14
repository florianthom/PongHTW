#include "Szene1.h"
#include "objects.hpp"

// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(-79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach rechts gegangen
// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach links gegangen

// DAS HEIST: ALLE NAMEN MIT LEFT BORDER ZUM BEISPIEL STIMMEN NICHT -> RICHTUNG MUSS IMMER UMGEKEHRT GENOMMEN WERDEN UM TATSÄCHLICHE TRANSLATIONSRICHTUNG ZU BEKOMMEN
// BIESPIEL: ModelRightBorder SPRICHT DIE LINKEBORDER AN -> MAN NIMMT MODELRIGHTMODER WEG D.h. linke Border geht weg


Szene1::Szene1(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse) : State()
{
	View = v;
	Projection = p;
	programmID = programID;
	ModelTopBorder = glm::mat4(1.0f);
	ModelButtomBorder = glm::mat4(1.0f);
	ModelLeftBorder = glm::mat4(1.0f);
	ModelRightBorder = glm::mat4(1.0f);
	ball1 = new Ball(programmID, View, Projection, glm::vec3(1.0f, 1.0f, 0.0f));


	ModelTopBorder = glm::scale(ModelTopBorder, glm::vec3(2 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelTopBorder = glm::translate(ModelTopBorder, glm::vec3(0, 30.0 * groesse, 0.0));

	ModelButtomBorder = glm::scale(ModelButtomBorder, glm::vec3(2 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelButtomBorder = glm::translate(ModelButtomBorder, glm::vec3(0, -30.0 * groesse, 0.0));

	// mitte = wie viel , vec3=Achse um die gedreht werden soll
	ModelRightBorder = glm::scale(ModelRightBorder, glm::vec3(1.0 / 40.0, 0.75 * groesse, 1.0 / 40.0));
	ModelRightBorder = glm::translate(ModelRightBorder, glm::vec3(79 * groesse, 0.0, 0.0));

	ModelLeftBorder = glm::scale(ModelLeftBorder, glm::vec3(1.0 / 40.0, 0.75 * groesse, 1.0 / 40.0));
	ModelLeftBorder = glm::translate(ModelLeftBorder, glm::vec3(-79 * groesse, 0.0, 0.0));

}

void Szene1::printMat4(glm::mat4 matrix) {

	//double dArray[4][4] = { 0.0 };
	std::cout << "\n\t\tSTART\n\n";

	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			std::cout << matrix[b][a] << "  "; // [b][a] da in OpenGL: column, row -> eigentlich(normal): row, column
			if (b == 3) std::cout << "\n" << std::endl;
		}
	}
	std::cout << "\t\t ENDE\n" << std::endl;

}




void Szene1::sendModel(glm::mat4 ModelToSend) {
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

void Szene1::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	//sendModel();
}
void Szene1::drawSzene() {
	/*Model = glm::translate(Model, move);
	sendModel();
	drawSphere(10, 10);*/
	//std::cout << ModelTopBorder << std::endl;
	//printMat4(ModelTopBorder);

	Collision::doWallCollision(&ModelTopBorder, ball1, glm::vec3(0.0f, -1.0f, 0.0f));
	Collision::doWallCollision(&ModelButtomBorder, ball1, glm::vec3(0.0f, 1.0f, 0.0f));
	Collision::doWallCollision(&ModelLeftBorder, ball1, glm::vec3(-1.0f, 0.0f, 0.0f));
	Collision::doWallCollision(&ModelRightBorder, ball1, glm::vec3(1.0f, 0.0f, 0.0f));
	ball1->moveBall();


	sendModel(ModelTopBorder);
	drawCube();


	
	sendModel(ModelButtomBorder);
	drawCube();

	
	sendModel(ModelRightBorder);
	drawCube();

	printMat4(ModelLeftBorder);
	sendModel(ModelLeftBorder);
	drawCube();/*
	std::cout << "test" << std::endl;*/
}


Szene1::~Szene1()
{
}

void Szene1::enterState() {
	ball1->set_initial_position();
}
void Szene1::exitState() {

}
