#include "MainMenu.h"
#include "objects.hpp"

// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(-79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach rechts gegangen
// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach links gegangen

// DAS HEIST: ALLE NAMEN MIT LEFT BORDER ZUM BEISPIEL STIMMEN NICHT -> RICHTUNG MUSS IMMER UMGEKEHRT GENOMMEN WERDEN UM TATSÄCHLICHE TRANSLATIONSRICHTUNG ZU BEKOMMEN
// BIESPIEL: ModelRightBorder SPRICHT DIE LINKEBORDER AN -> MAN NIMMT MODELRIGHTMODER WEG D.h. linke Border geht weg


MainMenu::MainMenu(GLuint* programID, glm::mat4* v, glm::mat4* p)
{
	View = v;
	Projection = p;
	programmID = programID;
	
	ModelAll = glm::mat4(1.0f);


}

void MainMenu::printMat4(glm::mat4 matrix) {

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




void MainMenu::sendModel(glm::mat4 ModelToSend) {
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

void MainMenu::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	//sendModel();
}
void MainMenu::drawSzene() {
	/*Model = glm::translate(Model, move);
	sendModel();
	drawSphere(10, 10);*/
	//std::cout << ModelTopBorder << std::endl;
	//printMat4(ModelTopBorder);



	sendModel(ModelAll);
	drawCube();

}


MainMenu::~MainMenu()
{
}
