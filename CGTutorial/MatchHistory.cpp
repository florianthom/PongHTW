#include "MatchHistory.h"

MatchHistory::~MatchHistory()
{
}

static bool sort_using_greater_than(double u, double v)
{
	return u > v;
}

MatchHistory::MatchHistory(GLuint* programID, glm::mat4* v, glm::mat4* p, double groessePara) : State()
{
	View = v;
	Projection = p;
	programmID = programID;
	groesse = groessePara;
	ModelAll = glm::mat4(1.0f);
	ModelAll = glm::scale(ModelAll, glm::vec3(1.7 * groesse, 1.3 / 1.0, 1.0 / 1.0));
	TextureOrange = loadBMP_custom("orange.bmp");

	history = read_file_and_save_in_list();
	initText2D("Holstein.DDS");
}

void MatchHistory::printMat4(glm::mat4 matrix) {

	std::cout << "\n\t\tSTART\n\n";

	for (int a = 0; a < 4; ++a) {
		for (int b = 0; b < 4; ++b) {
			std::cout << matrix[b][a] << "  "; // [b][a] da in OpenGL: column, row -> eigentlich(normal): row, column
			if (b == 3) std::cout << "\n" << std::endl;
		}
	}
	std::cout << "\t\t ENDE\n" << std::endl;

}




void MatchHistory::sendModel(glm::mat4 ModelToSend) {
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

void MatchHistory::setMVP(glm::mat4* v, glm::mat4* p) {
	View = v;
	Projection = p;
}
void MatchHistory::drawSzene() {
	glBindTexture(GL_TEXTURE_2D, TextureOrange);

	sendModel(ModelAll);
	drawCube();
	char headline[256];
	sprintf(headline, "MATCH HISTORY");
	int y = 450;
	printText2D(headline, 160, y, 40);
	glUseProgram(*programmID);
	char comment[256];
	sprintf(comment, "(last 5 matches only for 1vs1)");
	printText2D(comment, 180, 420, 15);
	glUseProgram(*programmID);
	char comment2[256];
	sprintf(comment2, "II oldest to newest II");
	printText2D(comment2, 270, 390, 12);
	glUseProgram(*programmID);


	std::string date = append_space_at_end_of_string_to_given_max_size(std::string("Date"),9);
	std::string time = append_space_at_end_of_string_to_given_max_size(std::string("Time"),6);
	std::string score1 = append_space_at_end_of_string_to_given_max_size(std::string("Score1"),7);
	std::string score2 = append_space_at_end_of_string_to_given_max_size(std::string("Score2"), 6);

	std::string total0 = date + time + score1 + score2;

	char text3[256];
	const char * tmp3 = total0.c_str();
	sprintf(text3, tmp3);
	int y3 = 330;
	printText2D(text3, 190, y3, 18);
	glUseProgram(*programmID);

	if (history.size() > 5) {
		std::vector< std::vector<std::string> >  y(history.end() - 5, history.end());
		history = y;
	}

	// history-vector contains x elements with each 7 elements(date,hour,and so on)
	// day, month, year, Hour, Min, points_player0, points_player1
	for (int i = 0; (i < history.size() && i < 5); i++) { //
		char text[256];
		std::string day = append_space_at_end_of_string_to_given_max_size(history[i][0],3);
		std::string month = append_space_at_end_of_string_to_given_max_size(history[i][1], 2);
		std::string year = append_space_at_end_of_string_to_given_max_size(history[i][2], 8);
		std::string hour = append_space_at_end_of_string_to_given_max_size(history[i][3], 2);
		std::string min = append_space_at_end_of_string_to_given_max_size(history[i][4], 7); // 7 to create space between date and score
		std::string pP1 = append_space_at_end_of_string_to_given_max_size(history[i][5], 8);
		std::string pP2 = append_space_at_end_of_string_to_given_max_size(history[i][6], 4);
		std::string total = day + month + year + hour + std::string(":") + min + pP1 + pP2;

		std::string tmp1 = total;
		const char * tmp2 = tmp1.c_str();
		sprintf(text, tmp2);
		int y = 280 - (i * 50);
		printText2D(text, 170, y, 15);
		glUseProgram(*programmID);
	}


}

std::string MatchHistory::append_space_at_end_of_string_to_given_max_size(std::string string, unsigned int max_size) {
	unsigned current_size = string.size();
	unsigned int chars_i_have_to_add1 = max_size - current_size;
	string.resize(current_size + chars_i_have_to_add1, ' ');
	return string;
}

const char * MatchHistory::convertToStr(double * var) {
	std::ostringstream ss;
	ss << *var;
	return ss.str().c_str();
}

void MatchHistory::lol() {
	std::cout << "1" << std::endl;

}
void MatchHistory::enterState() {

	//write_one_row(5,3);


}
void MatchHistory::exitState() {

}

// goal: write: date player0-score
//				player0-score
//				player1-score
//		repeat...
// so: 3 rows are needed for 1 total information
void MatchHistory::write_one_row(int points_player0,int points_player1) {
	std::fstream appendFileToWorkWith;

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	int Hour = now->tm_hour;
	int Min = now->tm_min;
	int Sec = now->tm_sec;

	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;


	char text[256];
	sprintf(text, "%i %i %i %i %i %i %i", day, month, year, Hour, Min, points_player0, points_player1);

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


std::vector< std::vector<std::string> > MatchHistory::read_file_and_save_in_list() {
	std::ifstream input(filename);
	std::vector< std::vector<std::string> > myVector; // equals ca. ArrayList

	for (std::string line; getline(input, line); )
	{

		std::istringstream buf(line);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);
		myVector.push_back(tokens);
		
	}
	input.close();
	return myVector;
}