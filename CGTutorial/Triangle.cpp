#include "Triangle.h"
#include "objects.hpp"


Triangle::Triangle(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse) : State()
{
	glUseProgram(*programID);
	View = v;
	Projection = p;
	programmID = programID;
	ModelTriangle = glm::mat4(1.0f);


	ModelTriangle = glm::scale(ModelTriangle, glm::vec3(4.f, 3.6f / 1.0, 2.5 / 1.0));
	VAO1 = createTriangle();
	initText2D("Holstein.DDS");

	TextureOrange = loadBMP_custom("orange.bmp");

}

void Triangle::printMat4(glm::mat4 matrix) {

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




void Triangle::sendModel(glm::mat4 ModelToSend) {
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

void Triangle::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
	//sendModel();
}

void Triangle::drawTriangleThroughObject(GLuint TextureOrange) {

	glBindTexture(GL_TEXTURE_2D, TextureOrange);
	sendModel(ModelTriangle);
	drawTriangle(VAO1);

	char text[256];
	sprintf(text, "PLAY PONG (1)");
	printText2D(text, 270, 250, 20);
	glUseProgram(*programmID);
	printControlKeysToConsole();
}

void Triangle::drawSzene() {

	glBindTexture(GL_TEXTURE_2D, TextureOrange);
	sendModel(ModelTriangle);
	drawTriangle(VAO1);
	int size = 16;

	char text0[256];
	sprintf(text0, "MAIN MENU (1)");
	printText2D(text0, 270, 400, size);
	glUseProgram(*programmID);
	char text[256];
	sprintf(text, "PLAY PONG 1 Player (2)");
	printText2D(text, 270, 360, size);
	glUseProgram(*programmID);
	char textq[256];
	sprintf(textq, "PLAY PONG 2 Player (3)");
	printText2D(textq, 270, 320, size);
	glUseProgram(*programmID);
	char text2[256];
	sprintf(text2, "PLAY PONG ADVANCED 1 Player (4)");
	printText2D(text2, 180, 280, size);
	glUseProgram(*programmID);
	char text2q[256];
	sprintf(text2q, "PLAY PONG ADVANCED 2 Player (5)");
	printText2D(text2q, 180, 240, size);
	glUseProgram(*programmID);
	char text2w[256];
	sprintf(text2w, "PLAY PONG ADVANCED 3 Player (6)");
	printText2D(text2w, 180, 200, size);
	glUseProgram(*programmID);
	char text2e[256];
	sprintf(text2e, "PLAY PONG ADVANCED 4 Player (7)");
	printText2D(text2e, 180, 160, size);
	glUseProgram(*programmID);
	char text3[256];
	sprintf(text3, "PLAY PONG IN real 3D (8)");
	printText2D(text3, 160, 120, size);
	glUseProgram(*programmID);
	char text4[256];
	sprintf(text4, "Highscore (9)");
	printText2D(text4, 270, 80, size);
	glUseProgram(*programmID);
	char text5[256];
	sprintf(text5, "Match History (0)");
	printText2D(text5, 270, 40, size);
	glUseProgram(*programmID);



	printControlKeysToConsole();
}


Triangle::~Triangle()
{
}

void Triangle::printControlKeysToConsole() {
	std::cout << "1: START PONG\n" << "2: RETURN TO MENU" << std::endl;
}
void Triangle::enterState() {
}
void Triangle::exitState() {
}

Triangle::Triangle() {

}
void Triangle::lol() {
	std::cout << "1" << std::endl;

}
