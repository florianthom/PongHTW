#include "Szene3.h"
#include "objects.hpp"


// InitBalkenModel = Transparenter Balken = Spieler Panel
//InitBalkenModel2 = nicht transparenter Balken
Szene3::Szene3(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse) : State()
{
	programmID = programID;
	View = v;
	Projection = p;


	player1Points = 0;
	player2Points = 0;

	ball1 = new Ball(programmID, v, p,true);

	player1 = new PlayerPaddle(programID, v, p, glm::vec3(0.0f, 0.0f, -30.0), 0, true); // l = location = 0 = links
	player2 = new CPUPaddle(programID, v, p, glm::vec3(0.0f, 0.0f, -10.0f), 2,true); // 2 = location = 0 = links

	EnvironmentCube = glm::mat4(1.0f);
	EnvironmentCube = glm::scale(EnvironmentCube, glm::vec3(2.0 / 1, 2.0 / 1, 5.0 / 1));

	TextureMandrill = loadBMP_custom("mandrill.bmp");
	TextureStripes = loadBMP_custom("streifen-maritim-1_1.bmp");
	TextureGreen = loadBMP_custom("green.bmp");
	TextureStone = loadBMP_custom("Steinwand.bmp");
	GLuint TextureOrange = loadBMP_custom("orange.bmp");


	initText2D("Holstein.DDS");


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



	glBindTexture(GL_TEXTURE_2D, TextureStone);
	sendModel(EnvironmentCube);
	drawCube();
	glBindTexture(GL_TEXTURE_2D, TextureGreen);

	Collision::do3DWallBallCollision(&EnvironmentCube, ball1);
	ball1->moveBall();

	player2->movePaddle(); // CPU paddle
	player1->movePaddle3D();







	glBindTexture(GL_TEXTURE_2D, TextureGreen);
	//sendModel(InitialBalkenModel2);
	//drawCube();

	//sendModel(InitialBalkenModel);
	//drawCubeWithBlending();
	
	glBindTexture(GL_TEXTURE_2D, TextureMandrill);


	sprintf(text, "Player1: %d  :  Player2: %d", player1Points, player2Points);
	printText2D(text, 90, 100, 25);
	glUseProgram(*programmID);
	


}


void Szene3::doPlayerInput(glm::vec3 input, int l, bool threeD) {
	if(threeD)
		player1->setInput(input);

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



//
//switch (location)
//{
//case 0:
//	if (!(Collision::checkCollision(&ModelE, player1_1) ||
//		Collision::checkCollision(&ModelD, player1_1))) {
//		player1_1->setInput(input);
//	}
//	else {
//		if (Collision::checkCollision(&ModelD, player1_1)) {
//			player1_1->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
//		}
//		else {
//			player1_1->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
//		}
//	}
//	break;
//case 1:
//	if (!(Collision::checkCollision(&ModelF, player1_2) ||
//		Collision::checkCollision(&ModelC, player1_2))) {
//		player1_2->setInput(input);
//	}
//	else {
//		if (Collision::checkCollision(&ModelF, player1_2)) {
//			player1_2->setInput(glm::vec3(-0.001f, 0.0f, 0.0f));
//		}
//		else {
//			player1_2->setInput(glm::vec3(0.001f, 0.0f, 0.0f));
//		}
//	}
//	break;
//case 2:
//	if (!(Collision::checkCollision(&ModelA, player2_1) ||
//		Collision::checkCollision(&ModelH, player2_1))) {
//		player2_1->setInput(input);
//	}
//	else {
//		if (Collision::checkCollision(&ModelA, player2_1)) {
//			player2_1->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
//		}
//		else {
//			player2_1->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
//		}
//	}
//	break;
//case 3:
//	if (!(Collision::checkCollision(&ModelG, player2_2) ||
//		Collision::checkCollision(&ModelB, player2_2))) {
//		player2_2->setInput(input);
//	}
//	else {
//		if (Collision::checkCollision(&ModelG, player2_2)) {
//			player2_2->setInput(glm::vec3(-0.001f, 0.0f, 0.0f));
//		}
//		else {
//			player2_2->setInput(glm::vec3(0.001f, 0.0f, 0.0f));
//		}
//	}
//	break;
//default:
//	printf("Ungueltige Position");
//}