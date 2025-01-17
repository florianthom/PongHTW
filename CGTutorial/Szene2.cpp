#include "Szene2.h"

Szene2::Szene2(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse,int player_numberPara) : State()
{
	player_number = player_numberPara;
	programmID = programID;
	View = v;
	Projection = p;
	ModelTopBorder = glm::mat4(1.0f);
	ModelButtomBorder = glm::mat4(1.0f);
	ModelLeftBorder = glm::mat4(1.0f);
	ModelRightBorder = glm::mat4(1.0f);

	width = 1 * groesse;
	height = 1.0f / 40.0f;
	depth = 1.0f / 40.0f;

	ModelA = glm::mat4(1.0f);
	ModelB = glm::mat4(1.0f);
	ModelC = glm::mat4(1.0f);
	ModelD = glm::mat4(1.0f);
	ModelE = glm::mat4(1.0f);
	ModelF = glm::mat4(1.0f);
	ModelG = glm::mat4(1.0f);
	ModelH = glm::mat4(1.0f);

	initText2D("Holstein.DDS");
	
	player1Points = 0;
	player2Points = 0;


	// top and buttom
	ModelTopBorder = glm::scale(ModelTopBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelTopBorder = glm::translate(ModelTopBorder, glm::vec3(0, 80.0 * groesse, 0.0));

	ModelButtomBorder = glm::scale(ModelButtomBorder, glm::vec3(1 * groesse, 1.0 / 40.0, 1.0 / 40.0));
	ModelButtomBorder = glm::translate(ModelButtomBorder, glm::vec3(0, -80.0 * groesse, 0.0));

	// left and right
	ModelRightBorder = glm::scale(ModelRightBorder, glm::vec3(height, width, depth));
	ModelRightBorder = glm::translate(ModelRightBorder, glm::vec3(-80 * groesse, 0.0f, 0.0f));

	ModelLeftBorder = glm::scale(ModelLeftBorder, glm::vec3(height, width, depth));
	ModelLeftBorder = glm::translate(ModelLeftBorder, glm::vec3(80 * groesse, 0.0f, 0.0f));

	//little verticals
	ModelC = glm::scale(ModelC, glm::vec3(height, 0.525 * groesse, depth));

	ModelC = glm::translate(ModelC, glm::vec3(-39 * groesse, 0.0f, 0.0f));
	ModelC = glm::translate(ModelC, glm::vec3(0.0f, 2.81 * groesse, 0.0f));

	ModelF = glm::scale(ModelF, glm::vec3(height, 0.525 * groesse, depth));

	ModelF = glm::translate(ModelF, glm::vec3(39 * groesse, 0.0f, 0.0f));
	ModelF = glm::translate(ModelF, glm::vec3(0.0f, 2.81 * groesse, 0.0f));

	ModelB = glm::scale(ModelB, glm::vec3(height, 0.525 * groesse, depth));

	ModelB = glm::translate(ModelB, glm::vec3(-39 * groesse, 0.0f, 0.0f));
	ModelB = glm::translate(ModelB, glm::vec3(0.0f, -2.81 * groesse, 0.0f));

	ModelG = glm::scale(ModelG, glm::vec3(height, 0.525 * groesse, depth));

	ModelG = glm::translate(ModelG, glm::vec3(39 * groesse, 0.0f, 0.0f));
	ModelG = glm::translate(ModelG, glm::vec3(0.0f, -2.81 * groesse, 0.0f));

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

	switch (player_number) {
	case 1:	player1_1 = new PlayerPaddle(programID, v, p, PLAYER1_1POSITION, 0);
			player1_2 = new PlayerPaddle(programID, v, p, PLAYER1_2POSITION, 1);
			player2_1 = new CPUPaddle(programID, v, p, PLAYER2_1POSITION, 2);
			player2_2 = new CPUPaddle(programID, v, p, PLAYER2_2POSITION, 3);
			break;
	case 2:	player1_1 = new PlayerPaddle(programID, v, p, PLAYER1_1POSITION, 0);
			player1_2 = new PlayerPaddle(programID, v, p, PLAYER1_2POSITION, 1);
			player2_1 = new PlayerPaddle(programID, v, p, PLAYER2_1POSITION, 2);
			player2_2 = new PlayerPaddle(programID, v, p, PLAYER2_2POSITION, 3);
			break;
	default:
			player1_1 = new CPUPaddle(programID, v, p, PLAYER1_1POSITION, 0);
			player1_2 = new CPUPaddle(programID, v, p, PLAYER1_2POSITION, 1);
			player2_1 = new CPUPaddle(programID, v, p, PLAYER2_1POSITION, 2);
			player2_2 = new CPUPaddle(programID, v, p, PLAYER2_2POSITION, 3);
	}

	ball1 = new Ball(programmID, v, p);

}


void Szene2::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
}

void Szene2::resetScene() {
	ball1->resetBall();
	player1_1->resetPaddle();
	player1_2->resetPaddle();
	player2_1->resetPaddle();
	player2_2->resetPaddle();
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
	for (int i = 0; i < 10; i++) {
		// Prueft, ob das erste Paddle (links) mit einer Wand kollidiert
		Collision::doWallCollision(&ModelD, player1_1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallCollision(&ModelE, player1_1, glm::vec3(0.0f, 1.0f, 0.0f));
		player1_1->movePaddle();

		// Prueft, ob das zweite Paddle (oben) mit einer Wand kollidiert
		Collision::doWallCollision(&ModelF, player1_2, glm::vec3(-1.0f, 0.0f, 0.0f));
		Collision::doWallCollision(&ModelC, player1_2, glm::vec3(1.0f, 0.0f, 0.0f));
		player1_2->movePaddle();

		// Prueft, ob das dritte Paddle (rechts) mit einer Wand kollidiert
		Collision::doWallCollision(&ModelA, player2_1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallCollision(&ModelH, player2_1, glm::vec3(0.0f, 1.0f, 0.0f));
		player2_1->movePaddle();

		// Prueft, ob das vierte Paddle (unten) mit einer Wand kollidiert
		Collision::doWallCollision(&ModelG, player2_2, glm::vec3(-1.0f, 0.0f, 0.0f));
		Collision::doWallCollision(&ModelB, player2_2, glm::vec3(1.0f, 0.0f, 0.0f));
		player2_2->movePaddle();


		// Falls Punkte relevante Wand getroffen wird
		if (Collision::checkCollision(&ModelLeftBorder, ball1)) {
			++player2Points;
			this->resetScene();
		}
		if (Collision::checkCollision(&ModelTopBorder, ball1)) {
			++player2Points;
			this->resetScene();
		}
		if (Collision::checkCollision(&ModelRightBorder, ball1)) {
			++player1Points;
			this->resetScene();
		}
		if (Collision::checkCollision(&ModelButtomBorder, ball1)) {
			++player1Points;
			this->resetScene();
		}

		// Prueft, ob Ball mit einer Wand kollidiert
		Collision::doWallBallCollision(&ModelC, ball1, glm::vec3(1.0f, 0.0f, 0.0f));
		Collision::doWallBallCollision(&ModelF, ball1, glm::vec3(-1.0f, 0.0f, 0.0f));
		Collision::doWallBallCollision(&ModelB, ball1, glm::vec3(1.0f, 0.0f, 0.0f));
		Collision::doWallBallCollision(&ModelG, ball1, glm::vec3(-1.0f, 0.0f, 0.0f));
		Collision::doWallBallCollision(&ModelD, ball1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallBallCollision(&ModelE, ball1, glm::vec3(0.0f, 1.0f, 0.0f));
		Collision::doWallBallCollision(&ModelA, ball1, glm::vec3(0.0f, -1.0f, 0.0f));
		Collision::doWallBallCollision(&ModelH, ball1, glm::vec3(0.0f, 1.0f, 0.0f));

		//Prueft, ob der Ball mit einem Paddle kollidiert ist
		Collision::doPaddleCollision(player1_1, ball1, player1_1->getLocation());
		Collision::doPaddleCollision(player1_2, ball1, player1_2->getLocation());
		Collision::doPaddleCollision(player2_1, ball1, player2_1->getLocation());
		Collision::doPaddleCollision(player2_2, ball1, player2_2->getLocation());

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

	sprintf(text_1, "Player1: %d", player1Points);
	printText2D(text_1, 35, 70, 20);
	glUseProgram(*programmID);

	sprintf(text_1, "Player2: %d", player2Points);
	printText2D(text_1, 570, 70, 20);
	glUseProgram(*programmID);
}

void Szene2::doPlayerInput(glm::vec3 input, int location) {
	switch (location)
	{
	case 0:
		if (!(Collision::checkCollision(&ModelE, player1_1) ||
			Collision::checkCollision(&ModelD, player1_1))) {
			player1_1->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelD, player1_1)) {
				player1_1->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
			}
			else {
				player1_1->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
			}
		}
		break;
	case 1:
		if (!(Collision::checkCollision(&ModelF, player1_2) ||
			Collision::checkCollision(&ModelC, player1_2))) {
			player1_2->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelF, player1_2)) {
				player1_2->setInput(glm::vec3(-0.001f, 0.0f, 0.0f));
			}
			else {
				player1_2->setInput(glm::vec3(0.001f, 0.0f, 0.0f));
			}
		}
		break;
	case 2:
		if (!(Collision::checkCollision(&ModelA, player2_1) ||
			Collision::checkCollision(&ModelH, player2_1))) {
			player2_1->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelA, player2_1)) {
				player2_1->setInput(glm::vec3(0.0f, -0.001f, 0.0f));
			}
			else {
				player2_1->setInput(glm::vec3(0.0f, 0.001f, 0.0f));
			}
		}
		break;
	case 3:
		if (!(Collision::checkCollision(&ModelG, player2_2) ||
			Collision::checkCollision(&ModelB, player2_2))) {
			player2_2->setInput(input);
		}
		else {
			if (Collision::checkCollision(&ModelG, player2_2)) {
				player2_2->setInput(glm::vec3(-0.001f, 0.0f, 0.0f));
			}
			else {
				player2_2->setInput(glm::vec3(0.001f, 0.0f, 0.0f));
			}
		}
		break;
	default:
		;
	}
}


Szene2::~Szene2()
{
}

void Szene2::exitState() {
	write_one_row_match_history(player1Points, player2Points);
	write_one_row_highscore(std::to_string(player1Points));
	write_one_row_highscore(std::to_string(player2Points));
}
void Szene2::enterState() {
}
Szene2::Szene2() {

}
void Szene2::lol() {

}