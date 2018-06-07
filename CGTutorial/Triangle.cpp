#include "Triangle.h"
#include "objects.hpp"


Triangle::Triangle(GLuint* programID, glm::mat4* v, glm::mat4* p, double groesse)
{
	glUseProgram(*programID);
	View = v;
	Projection = p;
	programmID = programID;
	ModelTriangle = glm::mat4(1.0f);


	ModelTriangle = glm::scale(ModelTriangle, glm::vec3(2.0f, 2.0 / 1.0, 2.0 / 1.0));
	VAO1 = createTriangle();


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

void Triangle::drawTriangleThroughObject() {

	sendModel(ModelTriangle);
	drawTriangle(VAO1);
}


Triangle::~Triangle()
{
}
