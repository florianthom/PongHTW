#include "Szene3.h"
#include "objects.hpp"


Szene3::Szene3(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse)
{
	programmID = programID;
	View = v;
	Projection = p;

	InitialBalkenModel = glm::mat4(1.0f);
	InitialBalkenModel = glm::scale(InitialBalkenModel, glm::vec3(1.0/1, 1.0 / 1, 1.0 / 1));

	InitialBalkenModel2 = glm::mat4(1.0f);
	InitialBalkenModel2 = glm::scale(InitialBalkenModel2, glm::vec3(1.0 / 5, 1.0 / 5, 1.0 / 5));



}

void Szene3::printMat4(glm::mat4 matrix) {

	//double dArray[4][4] = { 0.0 };
	std::cout << "\n\t\tSTART\n\n";

	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			std::cout << matrix[a][b] << "  ";
			if (b == 3) std::cout << "\n" << std::endl;
		}
	}
	std::cout << "\t\t ENDE\n" << std::endl;

}




void Szene3::sendModel(glm::mat4 ModelToSend) {
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

void Szene3::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	//sendModel();
}
void Szene3::drawSzene() {
	/*Model = glm::translate(Model, move);
	sendModel();
	drawSphere(10, 10);*/
	//std::cout << ModelTopBorder << std::endl;
	printMat4(InitialBalkenModel);


	//sendModel(InitialBalkenModel2);
	//drawCube();

	/*sendModel(InitialBalkenModel);
	drawCube();*/




}


Szene3::~Szene3()
{
}
