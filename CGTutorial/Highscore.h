#include "State.h"
#include "texture.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "text2D.h"
#include "objects.hpp"
#pragma once


class Highscore :
	public State
{
private:
	// High-score data: score and player name.
	
	GLuint* programmID;
	glm::mat4 ModelAll;
	glm::mat4 * View;
	glm::mat4 * Projection;
	glm::vec3 Position;
	double groesse;
	void sendModel(glm::mat4 ModelToSend);
	GLuint TextureOrange;
	char filename[15] = "highscores.txt";
	std::vector<double> highscore_vector;




public:
	Highscore(GLuint * programID, glm::mat4* v, glm::mat4* p, double groesse);
	~Highscore();
	virtual void drawSzene();
	void setMVP(glm::mat4* v, glm::mat4* p);
	void printMat4(glm::mat4 ModelToSend);
	void enterState() override;
	void exitState();
	void write_one_row(std::string text);
	void lol();
	std::vector<double> read_file_and_save_in_list();
	const char * convertToStr(double * var);

};

