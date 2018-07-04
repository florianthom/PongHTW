// Got Renamed to Math History

#include "Highscore.h"

Highscore::~Highscore()
{
}

static bool sort_using_greater_than(double u, double v)
{
	return u > v;
}

Highscore::Highscore(GLuint* programID, glm::mat4* v, glm::mat4* p, double groessePara) : State()
{
	View = v;
	Projection = p;
	programmID = programID;
	groesse = groessePara;
	ModelAll = glm::mat4(1.0f);
	ModelAll = glm::scale(ModelAll, glm::vec3(1.7 * groesse, 1.3 / 1.0, 1.0 / 1.0));
	TextureOrange = loadBMP_custom("orange.bmp");

	highscore_vector = read_file_and_save_in_list();
	std::sort(highscore_vector.begin(), highscore_vector.end(), sort_using_greater_than);
	initText2D("Holstein.DDS");



}

void Highscore::printMat4(glm::mat4 matrix) {

	std::cout << "\n\t\tSTART\n\n";

	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			std::cout << matrix[b][a] << "  "; // [b][a] da in OpenGL: column, row -> eigentlich(normal): row, column
			if (b == 3) std::cout << "\n" << std::endl;
		}
	}
	std::cout << "\t\t ENDE\n" << std::endl;

}




void Highscore::sendModel(glm::mat4 ModelToSend) {
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

void Highscore::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
}
void Highscore::drawSzene() {
	glBindTexture(GL_TEXTURE_2D, TextureOrange);

	sendModel(ModelAll);
	drawCube();

	char headline[256];
	sprintf(headline, "HIGHSCORES");
	int y = 450 ;
	printText2D(headline, 200, y, 40);
	glUseProgram(*programmID);


	for (int i = 0; (i < highscore_vector.size() && i < 5); i++) { //
		char text[256];
		std::string tmp1 = std::to_string(int(highscore_vector[i]));
		const char * tmp2 = tmp1.c_str();
		sprintf(text,"%d. place: \t %10s",i+1, tmp2);
		int y = 330 - (i*50);
		printText2D(text, 170, y, 20);
		glUseProgram(*programmID);
}


}

const char * Highscore::convertToStr(double * var) {
	std::ostringstream ss;
	ss << *var;
	return ss.str().c_str();
}

void Highscore::lol() {
	std::cout << "1" << std::endl;

}
void Highscore::enterState() {

}
void Highscore::exitState() {

}

void Highscore::write_one_row(std::string text) {
	std::fstream appendFileToWorkWith;

	appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


	// If file does not exist, Create new file
	if (!appendFileToWorkWith)
	{
		std::cout << "Cannot open file, file does not exist. Creating new file..";

		appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
	}

	appendFileToWorkWith << text << "\n";
	appendFileToWorkWith.close();
	std::cout << "\n";

}


std::vector<double> Highscore::read_file_and_save_in_list() {
	std::ifstream input(filename);

	std::vector<double> myVector;

	for (std::string line; getline(input, line); )
	{
		double score = atof(line.c_str());
		myVector.push_back(score);
	}
	input.close();
	return myVector;
}