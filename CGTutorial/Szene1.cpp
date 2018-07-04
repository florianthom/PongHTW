#include "Szene1.h"

// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(-79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach rechts gegangen
// Beachten: translatieren translate(ModelLeftBorder, glm::vec3(79 * groesse, 0.0, 0.0)) -> Ergebnis es wird intern nach links gegangen

// DAS HEIST: ALLE NAMEN MIT LEFT BORDER ZUM BEISPIEL STIMMEN NICHT -> RICHTUNG MUSS IMMER UMGEKEHRT GENOMMEN WERDEN UM TATSÄCHLICHE TRANSLATIONSRICHTUNG ZU BEKOMMEN
// BIESPIEL: ModelRightBorder SPRICHT DIE LINKEBORDER AN -> MAN NIMMT MODELRIGHTMODER WEG D.h. linke Border geht weg

Szene1::Szene1(GLuint* programID, glm::mat4* v, glm::mat4* p, double groessePara,int player_numberPara) : State()
{
	player_number = player_numberPara;
	View = v;
	Projection = p;
	programmID = programID;
	groesse = groessePara;
	ModelTopBorder = glm::mat4(1.0f);
	ModelButtomBorder = glm::mat4(1.0f);
	ModelLeftBorder = glm::mat4(1.0f);
	ModelRightBorder = glm::mat4(1.0f);

	player1Points = 0;
	player2Points = 0;
	ModelTopBorder = glm::scale(ModelTopBorder, glm::vec3(2 * groesse, 1.0 / 10.0, 1.0 / 10.0f));
	ModelTopBorder = glm::translate(ModelTopBorder, glm::vec3(0, 10.0 * groesse, 0.0));
	ModelButtomBorder = glm::scale(ModelButtomBorder, glm::vec3(2 * groesse, 1.0 / 10.0, 1.0 / 10.0f));
	ModelButtomBorder = glm::translate(ModelButtomBorder, glm::vec3(0, -10.0 * groesse, 0.0));
	// mitte = wie viel , vec3=Achse um die gedreht werden soll
	ModelRightBorder = glm::scale(ModelRightBorder, glm::vec3(1.0 / 5.0, 1.1 * groesse, 1.0 / 10.0f));
	ModelRightBorder = glm::translate(ModelRightBorder, glm::vec3(11 * groesse, 0.0, 0.0));
	ModelLeftBorder = glm::scale(ModelLeftBorder, glm::vec3(1.0 / 5.0, 1.1 * groesse, 1.0 / 10.0f));
	ModelLeftBorder = glm::translate(ModelLeftBorder, glm::vec3(-11 * groesse, 0.0, 0.0));
	initText2D("Holstein.DDS");

	ModelAll = new glm::mat4[4];
	ModelAll[0] = ModelRightBorder;
	ModelAll[1] = ModelTopBorder;
	ModelAll[2] = ModelLeftBorder;
	ModelAll[3] = ModelButtomBorder;

	normals = new glm::vec3[4];
	normals[0] = glm::vec3(-1.0f, 0.0f, 0.0f);
	normals[1] = glm::vec3(0.0f, -1.0f, 0.0f);
	normals[2] = glm::vec3(1.0f, 0.0f, 0.0f);
	normals[3] = glm::vec3(0.0f, 1.0f, 0.0f);
	
	//// Integerwert am Ende gibt die Position des Paddles an: 0 -> links, 1 -> oben, 2 -> rechts, 3 -> unten
	switch (player_number)
	{
	case 1:	player1 = new PlayerPaddle(programID, v, p, PLAYER1POSITION, 0);
			player2 = new CPUPaddle(programID, v, p, PLAYER2POSITION, 2);
			break;
	case 2:	player1 = new PlayerPaddle(programID, v, p, PLAYER1POSITION, 0);
			player2 = new PlayerPaddle(programID, v, p, PLAYER2POSITION, 2);
			break;
	default:
			player1 = new CPUPaddle(programID, v, p, PLAYER1POSITION, 0);
			player2 = new CPUPaddle(programID, v, p, PLAYER2POSITION, 2);
	}

	ball1 = new Ball(programmID, View, Projection);
	ball1->set_initial_position();
}



void Szene1::printMat4(glm::mat4 matrix) {

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

void Szene1::resetScene() {
	ball1->resetBall();
	player1->resetPaddle();
	player2->resetPaddle();
}

void Szene1::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
}

void Szene1::drawSzene() {
	
	sendModel(glm::mat4(1.0f));
	for (int i = 0; i < 10; i++) {
		//// Prueft, ob das erste Paddle mit einer Wand kollidiert und reagiert
		Collision::doWallCollision(&ModelTopBorder, player1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallCollision(&ModelButtomBorder, player1, glm::vec3(0.0f, 1.0f, 0.0f));
		player1->movePaddle();

		// Prueft, ob das zweite Paddle mit eíner Wand kollidiert und reagiert
		Collision::doWallCollision(&ModelTopBorder, player2, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallCollision(&ModelButtomBorder, player2, glm::vec3(0.0f, 1.0f, 0.0f));
		player2->movePaddle();

		Collision::doWallBallCollision(&ModelTopBorder, ball1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallBallCollision(&ModelButtomBorder, ball1, glm::vec3(0.0f, 1.0f, 0.0f));

		if (Collision::checkCollision(&ModelRightBorder, ball1)) {
			++player2Points;
			this->resetScene();
		}

		if (Collision::checkCollision(&ModelLeftBorder, ball1)) {
			++player1Points;
			this->resetScene();
		}

		Collision::doPaddleCollision(player1, ball1, player1->getLocation());
		Collision::doPaddleCollision(player2, ball1, player2->getLocation());

		ball1->moveBall();
	}


	sendModel(ModelTopBorder);
	drawCube();

	sendModel(ModelButtomBorder);
	drawCube();

	sendModel(ModelRightBorder);
	drawCube();

	sendModel(ModelLeftBorder);
	drawCube();

	sprintf(text, "Player1: %d  :  Player2: %d", player1Points, player2Points);
	printText2D(text, 90, 100, 25);
	glUseProgram(*programmID);
}


Szene1::~Szene1()
{
}

void Szene1::lol() {

}

void Szene1::enterState() {
	ball1->set_initial_position();
	ball1->set_initial_position();
}
void Szene1::exitState() {
	ball1->set_initial_position();
	write_one_row_match_history(player1Points, player2Points);
	write_one_row_highscore(std::to_string(player1Points));
	write_one_row_highscore(std::to_string(player2Points));
}

void Szene1::doPlayerInput(glm::vec3 input, int location) {
	switch (location)
	{
	case 0:
		if (!(Collision::checkCollision(&ModelTopBorder, player1) ||
			Collision::checkCollision(&ModelButtomBorder, player1))) {
			player1->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelTopBorder, player1)) {
				player1->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
			}
			else {
				player1->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
			}
		}

		break;
	case 1:
		break;
	case 2:
		if (!(Collision::checkCollision(&ModelTopBorder, player2) ||
			Collision::checkCollision(&ModelButtomBorder, player2))) {
			player2->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelTopBorder, player2)) {
				player2->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
			}
			else {
				player2->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
			}
		}
		break;
	case 3:
		break;
	default:
		;
	}
}


