#include "Szene3.h"
#include "objects.hpp"


Szene3::Szene3(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse) : State()
{
	programmID = programID;
	View = v;
	Projection = p;

	InitialBalkenModel = glm::mat4(1.0f);
	InitialBalkenModel = glm::scale(InitialBalkenModel, glm::vec3(1.0 / 5, 1.0 / 5, 1.0 / 5));
	InitialBalkenModel = glm::translate(InitialBalkenModel, glm::vec3(0.0, 0.0, -20.0));


	InitialBalkenModel2 = glm::mat4(1.0f);
	InitialBalkenModel2 = glm::scale(InitialBalkenModel2, glm::vec3(1.0 / 5, 1.0 / 5, 1.0 / 5));

	EnvironmentCube = glm::mat4(1.0f);
	EnvironmentCube = glm::scale(EnvironmentCube, glm::vec3(2.0 / 1, 2.0 / 1, 5.0 / 1));

	TextureMandrill = loadBMP_custom("mandrill.bmp");
	TextureStripes = loadBMP_custom("streifen-maritim-1_1.bmp");
	TextureGreen = loadBMP_custom("green.bmp");

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

	//*Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	*Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);



	glBindTexture(GL_TEXTURE_2D, TextureStripes);
	sendModel(EnvironmentCube);
	drawCube();
	glBindTexture(GL_TEXTURE_2D, TextureGreen);



	printMat4(InitialBalkenModel);


	glBindTexture(GL_TEXTURE_2D, TextureGreen);
	sendModel(InitialBalkenModel2);
	drawCube();

	sendModel(InitialBalkenModel);
	drawCubeWithBlending();
	
	glBindTexture(GL_TEXTURE_2D, TextureMandrill);


	


}


Szene3::~Szene3()
{
}
Szene3::Szene3(){

}
void Szene3::enterState() {

}
void Szene3::exitState() {

}

void Szene3::lol() {

}
